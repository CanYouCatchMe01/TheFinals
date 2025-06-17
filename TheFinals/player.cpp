#include "player.h"
#include "flecs/flecs.h"
#include "transform.h"
#include "camera.h"
#include "scene.h"
#include "PxPhysicsAPI.h"
#include "game.h"
#include <algorithm>
#include "physics.h"

namespace player {
    void update(scene::Scene &scene) {
        if (game::key_states[VK_RBUTTON]) {
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

            float mouse_velocity_speed_x = game::key_states[VK_RBUTTON] ? float(game::mouse_velocity_x) * rotation_speed : 0.0f;
            float mouse_velocity_speed_y = game::key_states[VK_RBUTTON] ? float(game::mouse_velocity_y) * rotation_speed : 0.0f;

            p.head_rotation_x += mouse_velocity_speed_y;
            p.head_rotation_x = std::clamp(p.head_rotation_x, -DirectX::XM_PIDIV2, DirectX::XM_PIDIV2);

            DirectX::XMVECTOR rot_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0, 1, 0, 0), mouse_velocity_speed_x);
            DirectX::XMVECTOR cam_rot = DirectX::XMLoadFloat4(&t.rotation);
            cam_rot = DirectX::XMQuaternionMultiply(cam_rot, rot_y);
            DirectX::XMStoreFloat4(&t.rotation, cam_rot);

            //float y_velocity = p.velocity.y + 9.81f * game::delta_time; // Gravity
            float y_velocity = 0.0f; // Gravity

            DirectX::XMFLOAT2 character_velocity = DirectX::XMFLOAT2(0, 0);
            if (game::key_states['D']) character_velocity.x += 1.0f;
            if (game::key_states['A']) character_velocity.x -= 1.0f;
            if (game::key_states['W']) character_velocity.y += 1.0f;
            if (game::key_states['S']) character_velocity.y -= 1.0f;

            float move_speed = 5.0f * game::delta_time;
            character_velocity.x *= move_speed;
            character_velocity.y *= move_speed;

            DirectX::XMVECTOR cam_right = DirectX::XMVector3Rotate(DirectX::XMVectorSet(1, 0, 0, 0), cam_rot);
            cam_right = DirectX::XMVectorMultiply(cam_right, DirectX::XMVectorSet(character_velocity.x, character_velocity.x, character_velocity.x, 0));
            DirectX::XMVECTOR cam_forward = DirectX::XMVector3Rotate(DirectX::XMVectorSet(0, 0, 1, 0), cam_rot);
            cam_forward = DirectX::XMVectorMultiply(cam_forward, DirectX::XMVectorSet(character_velocity.y, character_velocity.y, character_velocity.y, 0));

            physx::PxVec3 disp(
                DirectX::XMVectorGetX(cam_right) + DirectX::XMVectorGetX(cam_forward),
                y_velocity,
                DirectX::XMVectorGetZ(cam_right) + DirectX::XMVectorGetZ(cam_forward));

            physx::PxControllerCollisionFlags collision_flags = controller.controller->move(disp, 0.0, game::delta_time, physx::PxControllerFilters());

            if (collision_flags & physx::PxControllerCollisionFlag::eCOLLISION_DOWN) {
                p.velocity.y = 0.0f; // Reset vertical velocity when on the ground
            } else {
                p.velocity.y = y_velocity; // Apply gravity
            };
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

            DirectX::XMMATRIX player_matrix = DirectX::XMMatrixTranslation(player_transform.position.x, player_transform.position.y, player_transform.position.z);
            //DirectX::XMMATRIX head_matrix = player_matrix * DirectX::XMMatrixTranslation(0, player_player.head_height, 0);
            DirectX::XMMATRIX head_matrix = player_matrix;

            DirectX::XMVECTOR rot_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1, 0, 0, 0), player_player.head_rotation_x);
            DirectX::XMVECTOR rot_y = DirectX::XMLoadFloat4(&player_transform.rotation);
            DirectX::XMVECTOR rot = DirectX::XMQuaternionMultiply(rot_x, rot_y);
            DirectX::XMMATRIX head_rot_matrix = DirectX::XMMatrixRotationQuaternion(rot);
            head_matrix = head_rot_matrix * head_matrix;

            //DirectX::XMStoreFloat4x4(&camera.view, DirectX::XMMatrixInverse(nullptr, head_matrix));
            DirectX::XMStoreFloat4x4(&camera.view, DirectX::XMMatrixInverse(nullptr, head_matrix));
        }
    }
}