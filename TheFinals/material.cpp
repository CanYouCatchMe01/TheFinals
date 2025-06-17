#include "material.h"
#include "render_internal.h"
#include <vector>
#include <fstream>
#include "render.h"

namespace material {
    ID3D12RootSignature *root_signature = nullptr;
    ID3D12PipelineState *pipeline_state = nullptr;

    std::vector<char> read_file(const std::string &filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            // Handle error
            return {};
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> data(size);
        file.read(data.data(), size);

        file.close();
        return data;
    }

    void set_blend_state(D3D12_BLEND_DESC &blend_desc) {
        blend_desc = {};

        blend_desc.AlphaToCoverageEnable = FALSE;
        blend_desc.IndependentBlendEnable = FALSE;

        D3D12_RENDER_TARGET_BLEND_DESC default_render_target_blend_desc = {};
        default_render_target_blend_desc.BlendEnable = FALSE;
        default_render_target_blend_desc.LogicOpEnable = FALSE;
        default_render_target_blend_desc.SrcBlend = D3D12_BLEND_ONE;
        default_render_target_blend_desc.DestBlend = D3D12_BLEND_ZERO;
        default_render_target_blend_desc.BlendOp = D3D12_BLEND_OP_ADD;
        default_render_target_blend_desc.SrcBlendAlpha = D3D12_BLEND_ONE;
        default_render_target_blend_desc.DestBlendAlpha = D3D12_BLEND_ZERO;
        default_render_target_blend_desc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
        default_render_target_blend_desc.LogicOp = D3D12_LOGIC_OP_NOOP;
        default_render_target_blend_desc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

        for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
            blend_desc.RenderTarget[i] = default_render_target_blend_desc;
        }
    }

    void set_rasterizer_state(D3D12_RASTERIZER_DESC &rasterizer_desc) {
        rasterizer_desc = {};

        rasterizer_desc.FillMode = D3D12_FILL_MODE_SOLID;
        rasterizer_desc.CullMode = D3D12_CULL_MODE_BACK;
        rasterizer_desc.FrontCounterClockwise = FALSE;
        rasterizer_desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
        rasterizer_desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
        rasterizer_desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
        rasterizer_desc.DepthClipEnable = TRUE;
        rasterizer_desc.MultisampleEnable = FALSE;
        rasterizer_desc.AntialiasedLineEnable = FALSE;
        rasterizer_desc.ForcedSampleCount = 0;
        rasterizer_desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
    }

    void set_depth_stencil_state(D3D12_DEPTH_STENCIL_DESC &depth_stencil_desc) {
        depth_stencil_desc = {};

        depth_stencil_desc.DepthEnable = TRUE;
        depth_stencil_desc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
        depth_stencil_desc.DepthFunc = D3D12_COMPARISON_FUNC_GREATER;

        depth_stencil_desc.StencilEnable = FALSE;
        depth_stencil_desc.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
        depth_stencil_desc.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

        depth_stencil_desc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
        depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
        depth_stencil_desc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
        depth_stencil_desc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

        depth_stencil_desc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
        depth_stencil_desc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
        depth_stencil_desc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
        depth_stencil_desc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    }

    void setup() {

        std::vector<char> vs_shader = read_file("Shaders/vertex_shader.vs.cso");
        std::vector<char> ps_shader = read_file("Shaders/pixel_shader.ps.cso");

        HRESULT hr = render::device->CreateRootSignature(0, ps_shader.data(), ps_shader.size(), IID_PPV_ARGS(&root_signature));

        // Pipeline state
        D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
        pso_desc.pRootSignature = root_signature;
        pso_desc.VS.pShaderBytecode = vs_shader.data();
        pso_desc.VS.BytecodeLength = vs_shader.size();
        pso_desc.PS.pShaderBytecode = ps_shader.data();
        pso_desc.PS.BytecodeLength = ps_shader.size();
        set_blend_state(pso_desc.BlendState);
        pso_desc.SampleMask = UINT_MAX;
        set_rasterizer_state(pso_desc.RasterizerState);
        set_depth_stencil_state(pso_desc.DepthStencilState);

        D3D12_INPUT_ELEMENT_DESC input_elements[] = {
                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"INSTANCEROWA", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
                {"INSTANCEROWB", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
                {"INSTANCEROWC", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
                {"INSTANCEROWD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
                {"SRV_INDEX", 0, DXGI_FORMAT_R32_UINT, 1, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1},
        };

        pso_desc.InputLayout.pInputElementDescs = input_elements;
        pso_desc.InputLayout.NumElements = _countof(input_elements);
        pso_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
        pso_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        pso_desc.NumRenderTargets = 1;
        pso_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        pso_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
        pso_desc.SampleDesc.Count = 1;
        pso_desc.SampleDesc.Quality = 0;

        hr = render::device->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(&pipeline_state));
    }
}