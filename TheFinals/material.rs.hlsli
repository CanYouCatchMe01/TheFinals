#define SAMPLER_STATE_ANISOTROPIC_WARP "filter = FILTER_ANISOTROPIC, " \
"addressU = TEXTURE_ADDRESS_WRAP, " \
"addressV = TEXTURE_ADDRESS_WRAP, " \
"addressW = TEXTURE_ADDRESS_WRAP, " \
"mipLODBias = 0.0f, " \
"maxAnisotropy = 16, " \
"comparisonFunc = COMPARISON_ALWAYS, " \
"borderColor = STATIC_BORDER_COLOR_TRANSPARENT_BLACK, " \
"minLOD = 0.0f, " \
"maxLOD = 3.402823466e+38f, " \
"space = 0," \
"visibility = SHADER_VISIBILITY_PIXEL"

#define MATERIAL_RS "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT), " \
"CBV(b0, visibility = SHADER_VISIBILITY_VERTEX), " \
"DescriptorTable( SRV(t0, numDescriptors = unbounded), visibility = SHADER_VISIBILITY_PIXEL), " \
"StaticSampler(s0, " SAMPLER_STATE_ANISOTROPIC_WARP "), "