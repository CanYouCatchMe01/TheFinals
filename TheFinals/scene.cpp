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
#include "filter_group.h"

namespace scene {
    physx::PxShape *ground_shape = nullptr;
    physx::PxShape *cube_shape = nullptr;
    physx::PxMaterial *px_material = nullptr;

    void setup(Scene& scene) {
        px_material = physics::g_physics->createMaterial(0.6f, 0.6f, 0.f);

        physx::PxFilterData object_filter_data;
        object_filter_data.word0 = FilterGroup::Default;

        physx::PxBoxGeometry box = physx::PxBoxGeometry(physx::PxVec3(5.0, 0.5, 5.0));
        ground_shape = physics::g_physics->createShape(box, *px_material);
        ground_shape->setQueryFilterData(object_filter_data); //raycasting
        ground_shape->setSimulationFilterData(object_filter_data); //simulation

        physx::PxBoxGeometry box2 = physx::PxBoxGeometry(physx::PxVec3(0.5, 0.5, 0.5));
        cube_shape = physics::g_physics->createShape(box2, *px_material);
        cube_shape->setQueryFilterData(object_filter_data); //raycasting
        cube_shape->setSimulationFilterData(object_filter_data); //simulation

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

            physx::PxFilterData player_filter_data;
            player_filter_data.word0 = FilterGroup::Player; // Set the filter group for the player controller

            //Set the filter layer on the shapes
            physx::PxU32 num_shapes = controller.controller->getActor()->getNbShapes();
            physx::PxShape **s = new physx::PxShape * [num_shapes]; //array of pointers

            controller.controller->getActor()->getShapes(s, num_shapes, 0);

            //interate over the shapes and set the filter data
            for (physx::PxU32 i = 0; i < num_shapes; i++) {
                s[i]->setQueryFilterData(player_filter_data);
                s[i]->setSimulationFilterData(player_filter_data);
            }
            delete[] s;
                });

        //camera
        scene.world.entity()
            .insert([](camera::Camera &c) {
            constexpr float fov_y = DirectX::XMConvertToRadians(80.0f);
            float aspect_ratio = float(game::client_width) / float(game::client_height);
            float near_z = 1000.0f; //reverse depth
            float far_z = 0.1f;
            DirectX::XMMATRIX projection_matrix = DirectX::XMMatrixPerspectiveFovLH(fov_y, aspect_ratio, near_z, far_z);
            DirectX::XMStoreFloat4x4(&c.view, DirectX::XMMatrixIdentity());
            DirectX::XMStoreFloat4x4(&c.projection, projection_matrix);
                });

        //ground
        scene.world.entity()
            .insert([&](transform::Transform &t, model::Model& model, material::Material &material, physics::RigidStatic &rigid_static) {
            t.position = DirectX::XMFLOAT3(0, -2, 0);
            t.rotation = DirectX::XMFLOAT4(0, 0, 0, 1);
            t.scale = DirectX::XMFLOAT3(10, 1, 10);

            material.srv_index = render::STATIC_SRV::STONE_GRASS_TEXTURE;
            material.uv_scale = 10.0f;

            physx::PxTransform px_transform;
            physics::TransformToPxTransform(t, px_transform);

            rigid_static.rigid_static = physics::g_physics->createRigidStatic(px_transform);
            rigid_static.rigid_static->attachShape(*ground_shape);

            scene.physics_scene->addActor(*rigid_static.rigid_static);
                });

        //cube tower
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                scene.world.entity()
                    .insert([&](transform::Transform &t, model::Model &model, material::Material &material, physics::RigidDynamic &rigid_dynamic) {
                    t.position = DirectX::XMFLOAT3(i + 0.1 * i - 5.0f/2.0f, j + 0.1 * j, 3);
                    t.rotation = DirectX::XMFLOAT4(0, 0, 0, 1);
                    t.scale = DirectX::XMFLOAT3(1, 1, 1);

                    material.srv_index = render::STATIC_SRV::BRICK_TEXTURE;

                    physx::PxTransform px_transform;
                    physics::TransformToPxTransform(t, px_transform);

                    rigid_dynamic.rigid_dynamic = physics::g_physics->createRigidDynamic(px_transform);
                    rigid_dynamic.rigid_dynamic->attachShape(*cube_shape);
                    rigid_dynamic.rigid_dynamic->setMass(10.0f);

                    scene.physics_scene->addActor(*rigid_dynamic.rigid_dynamic);
                        });
            }
        }
    }

    void update(Scene& scene) {
        player::update(scene);
        physics::update(scene.physics_scene, scene.physics_accumulator, scene.world, game::delta_time);
        player::camera_update(scene.world);
    }
}
