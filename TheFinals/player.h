#pragma once
#include <DirectXMath.h>

namespace scene {
    struct Scene;
}

namespace flecs {
    struct world;
}

namespace player {
    struct Player {
        float head_height = 1.8f;
        float head_rotation_x = 0.0f;
        float head_rotation_y = 0.0f;
        DirectX::XMFLOAT3 velocity = DirectX::XMFLOAT3(0, 0, 0);
    };
    
    void update(scene::Scene &scene);
    void camera_update(flecs::world &world);
}
