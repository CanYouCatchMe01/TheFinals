#pragma once
#include <DirectXMath.h>

namespace transform {
    struct Transform {
        DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(0, 0, 0);
        DirectX::XMFLOAT4 rotation = DirectX::XMFLOAT4(0, 0, 0, 1); // Quaternion
        DirectX::XMFLOAT3 scale = DirectX::XMFLOAT3(1, 1, 1);
    };
}
