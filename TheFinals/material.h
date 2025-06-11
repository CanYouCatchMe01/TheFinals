#pragma once

struct ID3D12RootSignature;
struct ID3D12PipelineState;

namespace material {
    extern ID3D12RootSignature *root_signature;
    extern ID3D12PipelineState *pipeline_state;

    void setup();
}