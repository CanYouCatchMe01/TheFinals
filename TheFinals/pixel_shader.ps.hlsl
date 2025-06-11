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

Texture2D<float4> texture0 : register(t0);
SamplerState sampler0 : register(s0);

[RootSignature(MATERIAL_RS)]
float4 main(PSInput input) : SV_TARGET {
#if 1
    float3 texture_color = texture0.Sample(sampler0, input.uv).xyz;
    
    float3 dir_light_direction = normalize(float3(0, 0, 1));
    float dir_light_brightness = dot(input.normal, -dir_light_direction);
    float3 dir_light_final_color = dir_light_brightness * texture_color;
    
    float3 gamma_corrected_color = pow(dir_light_final_color.rgb, 1.0 / 2.2);
    return float4(gamma_corrected_color, 1.0);
#else
    float3 dir_light_color = float3(0.5, 0.5, 0.5);
    float3 dir_light_direction = normalize(float3(0, -1, 0));
    float dir_light_brightness = dot(input.normal, -dir_light_direction);
    float3 dir_light_final_color = dir_light_brightness * dir_light_color;
    
    float3 ambient_color = float3(1.0, 0.41, 0.70);
    float3 final_color = ambient_color + dir_light_final_color;
    
    return float4(final_color.x, final_color.y, final_color.z, 1.0);
#endif
}