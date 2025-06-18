#include "material.rs.hlsli"

struct VSInput {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : UV;
    
    float4 instance_row1 : INSTANCEROWA;
    float4 instance_row2 : INSTANCEROWB;
    float4 instance_row3 : INSTANCEROWC;
    float4 instance_row4 : INSTANCEROWD;
    uint srv_index : SRV_INDEX;
    float uv_scale : UV_SCALE;
};

struct PSInput {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : UV;
    uint srv_index : SRV_INDEX;
};

cbuffer FrameConstants : register(b0) {
    float4x4 view_proj;
};

[RootSignature(MATERIAL_RS)]
PSInput main(VSInput input) {
    PSInput output;
    
    float4x4 instance_transform = float4x4(
        input.instance_row1,
        input.instance_row2,
        input.instance_row3,
        input.instance_row4
    );
    
    float4 world_position = mul(float4(input.position, 1.0f), instance_transform);
    output.position = mul(world_position, view_proj);
    output.normal = normalize(mul(input.normal, (float3x3) instance_transform));
    output.uv = input.uv * input.uv_scale;
    output.srv_index = input.srv_index;

    return output;
}