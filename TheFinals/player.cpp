#include "player.h"
#include "flecs/flecs.h"
#include "transform.h"
#include "camera.h"
#include "scene.h"
#include "PxPhysicsAPI.h"
#include "game.h"
#include <algorithm>
#include "physics.h"
#include <cmath>
#include "filter_group.h"

namespace player {
    void update(scene::Scene &scene) {
        if (game::is_key_held_down(VK_RBUTTON)) {
            // Get the client rect (in client coordinates)
            RECT clientRect;
            GetClientRect(game::hwnd, &clientRect);

            // Calculate the center of the client area
            int centerX = (clientRect.right - clientRect.left) / 2;
            int centerY = (clientRect.bottom - clientRect.top) / 2;

            // Convert the center point to screen coordinates
            POINT pt = { centerX, centerY };
            ClientToScreen(game::hwnd, &pt);

            // Move the cursor to the center of the client area
            SetCursorPos(pt.x, pt.y);

            while (ShowCursor(FALSE) >= 0);
        } else {
            while (ShowCursor(TRUE) < 0);
        }

        scene.world.each([&](player::Player &p, transform::Transform &t, physics::Controller &controller) {
            float rotation_speed = 0.01f;

            float mouse_velocity_speed_x = game::is_key_held_down(VK_RBUTTON) ? float(game::mouse_velocity_x) * rotation_speed : 0.0f;
            float mouse_velocity_speed_y = game::is_key_held_down(VK_RBUTTON) ? float(game::mouse_velocity_y) * rotation_speed : 0.0f;

            p.head_rotation_x += mouse_velocity_speed_y;
            p.head_rotation_x = std::clamp(p.head_rotation_x, -DirectX::XM_PIDIV2, DirectX::XM_PIDIV2); //clamp up and down rotation

            p.head_rotation_y += mouse_velocity_speed_x;
            p.head_rotation_y = std::fmod(p.head_rotation_y, DirectX::XM_2PI); //makes so there are not very large values

            DirectX::XMVECTOR quat_rot_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0, 1, 0, 0), p.head_rotation_y);
            DirectX::XMStoreFloat4(&t.rotation, quat_rot_y); //just set

            float y_velocity = p.velocity.y - 9.81f * game::delta_time; // Gravity

            physx::PxControllerState state;
            controller.controller->getState(state);

            if (game::is_key_pressed(VK_SPACE) && (state.collisionFlags & physx::PxControllerCollisionFlag::eCOLLISION_DOWN)) {
                y_velocity = 4.0f; // Jump
            }

            DirectX::XMFLOAT2 character_velocity = DirectX::XMFLOAT2(0, 0);
            if (game::is_key_held_down('D')) character_velocity.x += 1.0f;
            if (game::is_key_held_down('A')) character_velocity.x -= 1.0f;
            if (game::is_key_held_down('W')) character_velocity.y += 1.0f;
            if (game::is_key_held_down('S')) character_velocity.y -= 1.0f;

            float move_speed = 5.0f * game::delta_time;
            character_velocity.x *= move_speed;
            character_velocity.y *= move_speed;

            DirectX::XMVECTOR cam_right = DirectX::XMVector3Rotate(DirectX::XMVectorSet(1, 0, 0, 0), quat_rot_y);
            cam_right = DirectX::XMVectorMultiply(cam_right, DirectX::XMVectorSet(character_velocity.x, character_velocity.x, character_velocity.x, 0));
            DirectX::XMVECTOR cam_forward = DirectX::XMVector3Rotate(DirectX::XMVectorSet(0, 0, 1, 0), quat_rot_y);
            cam_forward = DirectX::XMVectorMultiply(cam_forward, DirectX::XMVectorSet(character_velocity.y, character_velocity.y, character_velocity.y, 0));

            physx::PxVec3 disp(
                DirectX::XMVectorGetX(cam_right) + DirectX::XMVectorGetX(cam_forward),
                y_velocity * game::delta_time,
                DirectX::XMVectorGetZ(cam_right) + DirectX::XMVectorGetZ(cam_forward));

            physx::PxControllerCollisionFlags collision_flags = controller.controller->move(disp, 0.0, game::delta_time, physx::PxControllerFilters());

            if (collision_flags & physx::PxControllerCollisionFlag::eCOLLISION_DOWN) {
                p.velocity.y = 0.0f; // Reset vertical velocity when on the ground
            } else {
                p.velocity.y = y_velocity; // Apply gravity
            };

            //shoot
            if (game::is_key_pressed(VK_LBUTTON)) {

                physx::PxVec3 px_origin = physx::toVec3(controller.controller->getFootPosition());
                px_origin.y += p.head_height; // Adjust origin to head height

                DirectX::XMVECTOR rot_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1, 0, 0, 0), p.head_rotation_x);
                DirectX::XMVECTOR rot_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0, 1, 0, 0), p.head_rotation_y);
                DirectX::XMVECTOR rot = DirectX::XMQuaternionMultiply(rot_x, rot_y);

                DirectX::XMVECTOR head_forward = DirectX::XMVector3Rotate(DirectX::XMVectorSet(0, 0, 1, 0), rot);
                DirectX::XMFLOAT3 direction;
                DirectX::XMStoreFloat3(&direction, head_forward);

                physx::PxVec3 px_direction;
                physics::Float3ToPxVec3(direction, px_direction);

                physx::PxRaycastBuffer hit_buffer = {};
                physx::PxQueryFilterData filter_data;
                filter_data.data.word0 = ~FilterGroup::Player; //do not hit player

                scene.physics_scene->raycast(
                    px_origin,
                    px_direction,
                    1000.0f,
                    hit_buffer,
                    physx::PxHitFlag::eDEFAULT,
                    filter_data
                );

                if (hit_buffer.hasBlock) {
                    //add impulse to the object that was hit
                    physx::PxRigidDynamic *hit_rigid_dynamic = hit_buffer.block.actor->is<physx::PxRigidDynamic>();

                    if (hit_rigid_dynamic) {

                        if (hit_rigid_dynamic->getRigidBodyFlags() & physx::PxRigidBodyFlag::eKINEMATIC) {
                            int hey = 0;
                            hey;
                        }

                        // Calculate the impulse direction
                        physx::PxVec3 impulse_direction = px_direction.getNormalized();
                        // Apply an impulse to the hit object
                        hit_rigid_dynamic->addForce(impulse_direction * 100.0f, physx::PxForceMode::eIMPULSE);
                    }
                }
            }
            });
    }

    void camera_update(flecs::world &world) {

        flecs::entity player_entity;
        flecs::entity camera_entity;

        world.each([&](flecs::entity e, Player &p, transform::Transform& t) {
            player_entity = e;
            return;
            });

        world.each([&](flecs::entity e, camera::Camera &c) {
            camera_entity = e;
            return;
            });

        if (player_entity.is_valid() && camera_entity.is_valid()) {
            const transform::Transform &player_transform = player_entity.get<transform::Transform>();
            const player::Player &player_player = player_entity.get<player::Player>();
            camera::Camera &camera = camera_entity.get_mut<camera::Camera>();

            DirectX::XMMATRIX head_matrix = DirectX::XMMatrixTranslation(player_transform.position.x, player_transform.position.y + player_player.head_height, player_transform.position.z);

            DirectX::XMVECTOR rot_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1, 0, 0, 0), player_player.head_rotation_x);
            DirectX::XMVECTOR rot_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0, 1, 0, 0), player_player.head_rotation_y);
            DirectX::XMVECTOR rot = DirectX::XMQuaternionMultiply(rot_x, rot_y);
            DirectX::XMMATRIX head_rot_matrix = DirectX::XMMatrixRotationQuaternion(rot);
            head_matrix = head_rot_matrix * head_matrix;

            DirectX::XMStoreFloat4x4(&camera.view, DirectX::XMMatrixInverse(nullptr, head_matrix));
        }
    }
}