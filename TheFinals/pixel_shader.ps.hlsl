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
    uint srv_index : SRV_INDEX;
};

Texture2D textures[] : register(t0, space0);
SamplerState sampler0 : register(s0);

[RootSignature(MATERIAL_RS)]
float4 main(PSInput input) : SV_TARGET {
#if 1
    float3 texture_color = textures[input.srv_index].Sample(sampler0, input.uv).xyz;
    
    float3 dir_light_direction = normalize(float3(1, -1, 0));
    float dir_light_brightness = max(dot(input.normal, -dir_light_direction), 0.0f);
    float3 dir_light_color = 0.7 * dir_light_brightness * texture_color;
    float3 ambient_light_color = float3(0.1, 0.1, 0.1) * texture_color;
    float3 light_final_color = ambient_light_color + dir_light_color;
    
    float3 gamma_corrected_color = pow(light_final_color.rgb, 1.0 / 2.2);
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