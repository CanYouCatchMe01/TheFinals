#include "physics.h"
#include "PxPhysicsAPI.h"
#include "flecs/flecs.h"
#include "transform.h"

//#define PHYSX_DEBUG

#ifdef PHYSX_DEBUG
#pragma message("WARNING: PHYSX_DEBUG ENABLED, DO NOT COMMIT LIKE THIS!")
#endif

namespace physics {
    physx::PxDefaultAllocator g_default_allocator;
    physx::PxDefaultErrorCallback g_default_error_callback;

    physx::PxFoundation *g_foundation = NULL;
    physx::PxPhysics *g_physics = NULL;
    physx::PxDefaultCpuDispatcher *g_dispatcher = NULL;

#ifdef PHYSX_DEBUG 
    physx::PxPvd *globalPvd = NULL;
    physx::PxPvdTransport *globalTransport = NULL;
#endif

    void setup() {
		g_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, g_default_allocator, g_default_error_callback);

#ifdef PHYSX_DEBUG 
		globalPvd = PxCreatePvd(*globalFoundation);
		globalTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
		//globalPvd->connect(*globalTransport, physx::PxPvdInstrumentationFlag::eALL); //Not needed. Doing later
		bool recordMemoryAllocations = true;

		globalPhysics = PxCreatePhysics(
			PX_PHYSICS_VERSION,
			*globalFoundation,
			physx::PxTolerancesScale(),
			recordMemoryAllocations,
			globalPvd
		);

		PxInitExtensions(*globalPhysics, globalPvd);
#else
		g_physics = PxCreatePhysics(
			PX_PHYSICS_VERSION,
			*g_foundation,
			physx::PxTolerancesScale()
		);

		PxInitExtensions(*g_physics, nullptr);
#endif

		g_dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    }

	transform::Transform PxTransformToTransform(const physx::PxTransform &px_transform, const DirectX::XMFLOAT3 &scale) {
		transform::Transform transform = {};
        transform.position = DirectX::XMFLOAT3(px_transform.p.x, px_transform.p.y, px_transform.p.z);
        transform.rotation = DirectX::XMFLOAT4(px_transform.q.w, px_transform.q.x, px_transform.q.y, px_transform.q.z);
        transform.scale = scale;

		return transform;
	}

	DirectX::XMFLOAT3 PxExtendedVec3ToFloat3(const physx::PxExtendedVec3 &px_ext_vec3) {
        return DirectX::XMFLOAT3(px_ext_vec3.x, px_ext_vec3.y, px_ext_vec3.z);
	}

	void update(physx::PxScene* physics_scene, float physics_accumulator, flecs::world &world, float delta_time) {

        constexpr float fixed_delta_time = 1.0f / 60.0f;

		physics_accumulator += delta_time;

		while (physics_accumulator >= fixed_delta_time) {
			// Step physics
			physics_scene->simulate(fixed_delta_time);
			physics_scene->fetchResults(true);

			// Update physics-based components
			// (e.g., read back positions or apply forces)

			physics_accumulator -= fixed_delta_time;
		}

		world.each([](physics::RigidDynamic &rigid_dynamic, transform::Transform &transform) {
            transform = PxTransformToTransform(rigid_dynamic.rigid_dynamic->getGlobalPose(), transform.scale);
			});

		world.each([](physics::Controller &controller, transform::Transform &transform) {
			transform.position = PxExtendedVec3ToFloat3(controller.controller->getFootPosition());
			});
	}

	void create_scene(physx::PxScene **physics_scene, physx::PxControllerManager **controller_manager) {
		physx::PxSceneDesc scene_desc(g_physics->getTolerancesScale());
		scene_desc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
		scene_desc.cpuDispatcher = g_dispatcher;
		scene_desc.filterShader = physx::PxDefaultSimulationFilterShader;
		scene_desc.simulationEventCallback = nullptr;
		//scene_desc.flags |= physx::PxSceneFlag::eENABLE_CCD; //Enables continuous collision detection, mainly for weapon throw
		*physics_scene = g_physics->createScene(scene_desc);

		*controller_manager = PxCreateControllerManager(**physics_scene);
	}
}