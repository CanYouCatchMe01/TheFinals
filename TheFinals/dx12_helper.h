#pragma once
#include "render_internal.h"

namespace dx12_helper {
    UINT64 MyGetRequiredIntermediateSize(
        ID3D12Resource *destinationResource,
        UINT firstSubresource,
        UINT numSubresources);

    UINT64 MyUpdateSubresources(
        ID3D12GraphicsCommandList *cmdList,
        ID3D12Resource *destResource,
        ID3D12Resource *intermediate,
        UINT64 intermediateOffset,
        UINT firstSubresource,
        UINT numSubresources,
        const D3D12_SUBRESOURCE_DATA *srcData);
}