#pragma once
#include <DirectXMath.h>

namespace camera {
    //gets its position from the transform component
    struct Camera {
        DirectX::XMFLOAT4X4 view;
        DirectX::XMFLOAT4X4 projection;
    };
}
