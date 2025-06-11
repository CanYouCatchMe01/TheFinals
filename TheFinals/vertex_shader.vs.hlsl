#include "material.rs.hlsli"

struct VSInput {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : UV;
};

struct PSInput {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : UV;
};

cbuffer FrameConstants : register(b0) {
    float4x4 view_proj;
};

cbuffer ObjectConstants : register(b1) {
    float4x4 object_matrix;
};

[RootSignature(MATERIAL_RS)]
PSInput main(VSInput input) {
    PSInput output;
    
    float4 world_position = mul(float4(input.position, 1.0f), object_matrix);
    output.position = mul(world_position, view_proj);
    output.normal = normalize(mul(input.normal, (float3x3) object_matrix));
    output.uv = input.uv;

    return output;
}