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
    physx::PxPvd *g_pvd = NULL;
    physx::PxPvdTransport *g_transport = NULL;
#endif

	void PxTransformToTransform(const physx::PxTransform &in_transform, const DirectX::XMFLOAT3 &in_scale, transform::Transform &out_transform) {
		out_transform.position = DirectX::XMFLOAT3(in_transform.p.x, in_transform.p.y, in_transform.p.z);
		out_transform.rotation = DirectX::XMFLOAT4(in_transform.q.x, in_transform.q.y, in_transform.q.z, in_transform.q.w);
		out_transform.scale = in_scale;
	}

	void TransformToPxTransform(const transform::Transform &in_transform, physx::PxTransform &out_transform) {
		physx::PxVec3 pos(in_transform.position.x, in_transform.position.y, in_transform.position.z);
		physx::PxQuat rot(in_transform.rotation.x, in_transform.rotation.y, in_transform.rotation.z, in_transform.rotation.w);
        out_transform = physx::PxTransform(pos, rot);
	}

	void Float3ToPxVec3(const DirectX::XMFLOAT3 &in_float3, physx::PxVec3 &out_vec3) {
		out_vec3 = physx::PxVec3(in_float3.x, in_float3.y, in_float3.z);
	}

	void PxExtendedVec3ToFloat3(const physx::PxExtendedVec3 &in_ext_vec3, DirectX::XMFLOAT3& out_float3) {
		out_float3 = DirectX::XMFLOAT3(in_ext_vec3.x, in_ext_vec3.y, in_ext_vec3.z);
	}

    void setup() {
		g_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, g_default_allocator, g_default_error_callback);

#ifdef PHYSX_DEBUG 
		g_pvd = PxCreatePvd(*g_foundation);
		g_transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
		//globalPvd->connect(*globalTransport, physx::PxPvdInstrumentationFlag::eALL); //Not needed. Doing later
		bool recordMemoryAllocations = true;

		g_physics = PxCreatePhysics(
			PX_PHYSICS_VERSION,
			*g_foundation,
			physx::PxTolerancesScale(),
			recordMemoryAllocations,
			g_pvd
		);

		PxInitExtensions(*g_physics, g_pvd);
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

	void update(physx::PxScene* physics_scene, float &physics_accumulator, flecs::world &world, float delta_time) {

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
            PxTransformToTransform(rigid_dynamic.rigid_dynamic->getGlobalPose(), transform.scale, transform);
			});

		world.each([](physics::Controller &controller, transform::Transform &transform) {
			PxExtendedVec3ToFloat3(controller.controller->getFootPosition(), transform.position);
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

#ifdef PHYSX_DEBUG 
		//Reconnect PVD so the latest scene is visible in the program
		g_pvd->disconnect();
		g_pvd->connect(*g_transport, physx::PxPvdInstrumentationFlag::eALL);
#endif
	}
}