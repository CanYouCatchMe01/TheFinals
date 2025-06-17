#include "scene.h"
#include "physics.h"
#include "game.h"
#include "transform.h"
#include "player.h"
#include "PxPhysicsAPI.h"
#include "camera.h"
#include "own_model.h"
#include "material.h"
#include "static_srv.h"

namespace scene {
    physx::PxShape *ground_shape = nullptr;
    physx::PxShape *middle_shape = nullptr;
    physx::PxMaterial *px_material = nullptr;

    void setup(Scene& scene) {
        px_material = physics::g_physics->createMaterial(0.6f, 0.6f, 0.f);

        physx::PxBoxGeometry box = physx::PxBoxGeometry(physx::PxVec3(5.0, 0.5, 5.0));
        ground_shape = physics::g_physics->createShape(box, *px_material);

        physx::PxBoxGeometry box2 = physx::PxBoxGeometry(physx::PxVec3(0.5, 0.5, 0.5));
        middle_shape = physics::g_physics->createShape(box2, *px_material);

        physics::create_scene(&scene.physics_scene, &scene.controller_manager);

        //player
        scene.world.entity()
            .insert([&](transform::Transform &t, player::Player &p, physics::Controller &controller) {

            physx::PxCapsuleControllerDesc desc;
            desc.material = px_material;
            desc.slopeLimit = 0.707;
            desc.stepOffset = 0.1;
            desc.contactOffset = 0.1;
            desc.height = 1.8;
            desc.radius = 0.2;
            desc.position = physx::PxExtendedVec3(0.0, 0.0, 0.0);
            controller.controller = scene.controller_manager->createController(desc);
                });

        //camera
        scene.world.entity()
            .insert([](camera::Camera &c) {
            constexpr float fov_y = DirectX::XMConvertToRadians(60.0f);
            float aspect_ratio = float(game::client_width) / float(game::client_height);
            float near_z = 1000.0f; //reverse depth
            float far_z = 0.1f;
            DirectX::XMMATRIX projection_matrix = DirectX::XMMatrixPerspectiveFovLH(fov_y, aspect_ratio, near_z, far_z);
            DirectX::XMStoreFloat4x4(&c.view, DirectX::XMMatrixIdentity());
            DirectX::XMStoreFloat4x4(&c.projection, projection_matrix);
                });

        //ground
        scene.world.entity()
            .insert([&](transform::Transform &t, model::Model& model, material::Material &material, physics::RigidStatic rigid_static) {
            t.position = DirectX::XMFLOAT3(0, -2, 0);
            t.rotation = DirectX::XMFLOAT4(0, 0, 0, 1);
            t.scale = DirectX::XMFLOAT3(10, 1, 10);

            material.srv_index = render::STATIC_SRV::MAIN_TEXTURE;

            physx::PxTransform px_transform;
            physics::TransformToPxTransform(t, px_transform);

            rigid_static.rigid_static = physics::g_physics->createRigidStatic(px_transform);
            rigid_static.rigid_static->attachShape(*ground_shape);

            scene.physics_scene->addActor(*rigid_static.rigid_static);
                });

        //ground
        scene.world.entity()
            .insert([&](transform::Transform &t, model::Model &model, material::Material &material, physics::RigidStatic rigid_static) {
            t.position = DirectX::XMFLOAT3(0, 0, 1);
            t.rotation = DirectX::XMFLOAT4(0, 0, 0, 1);
            t.scale = DirectX::XMFLOAT3(1, 1, 1);

            material.srv_index = render::STATIC_SRV::MAIN_TEXTURE;

            physx::PxTransform px_transform;
            physics::TransformToPxTransform(t, px_transform);

            rigid_static.rigid_static = physics::g_physics->createRigidStatic(px_transform);
            rigid_static.rigid_static->attachShape(*middle_shape);

            scene.physics_scene->addActor(*rigid_static.rigid_static);
                });
    }

    void update(Scene& scene) {
        player::update(scene);
        physics::update(scene.physics_scene, scene.physics_accumulator, scene.world, game::delta_time);
        player::camera_update(scene.world);
    }
}
