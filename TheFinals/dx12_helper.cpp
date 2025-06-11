#include "dx12_helper.h"
#include <vector>

namespace dx12_helper {
    UINT64 MyGetRequiredIntermediateSize(
        ID3D12Resource *destinationResource,
        UINT firstSubresource,
        UINT numSubresources) {
        if (!destinationResource) return 0;

        D3D12_RESOURCE_DESC desc = destinationResource->GetDesc();
        ID3D12Device *device = nullptr;
        destinationResource->GetDevice(IID_PPV_ARGS(&device));

        UINT64 requiredSize = 0;
        device->GetCopyableFootprints(
            &desc,
            firstSubresource,
            numSubresources,
            0,                  // Base offset
            nullptr,            // We don't need layouts here
            nullptr,            // Or row counts
            nullptr,            // Or row sizes
            &requiredSize);     // Just want the total required size

        return requiredSize;
    }

    UINT64 MyUpdateSubresources(
        ID3D12GraphicsCommandList *cmdList,
        ID3D12Resource *destResource,
        ID3D12Resource *intermediate,
        UINT64 intermediateOffset,
        UINT firstSubresource,
        UINT numSubresources,
        const D3D12_SUBRESOURCE_DATA *srcData) {
        // Get the destination resource description
        D3D12_RESOURCE_DESC desc = destResource->GetDesc();
        UINT64 requiredSize = 0;

        // Compute layouts for each subresource
        std::vector<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> layouts(numSubresources);
        std::vector<UINT> numRows(numSubresources);
        std::vector<UINT64> rowSizesInBytes(numSubresources);

        ID3D12Device *device = nullptr;
        destResource->GetDevice(IID_PPV_ARGS(&device));

        device->GetCopyableFootprints(
            &desc,
            firstSubresource,
            numSubresources,
            intermediateOffset,
            layouts.data(),
            numRows.data(),
            rowSizesInBytes.data(),
            &requiredSize);

        // Map the upload (intermediate) resource
        BYTE *mappedData = nullptr;
        D3D12_RANGE readRange = { 0, 0 }; // We're not reading
        HRESULT hr = intermediate->Map(0, &readRange, reinterpret_cast<void **>(&mappedData));
        if (FAILED(hr)) {
            return 0;
        }

        // Copy data into mapped upload buffer
        for (UINT i = 0; i < numSubresources; ++i) {
            BYTE *dst = mappedData + layouts[i].Offset;
            const BYTE *src = reinterpret_cast<const BYTE *>(srcData[i].pData);

            for (UINT row = 0; row < numRows[i]; ++row) {
                memcpy(
                    dst + row * layouts[i].Footprint.RowPitch,
                    src + row * srcData[i].RowPitch,
                    rowSizesInBytes[i]);
            }
        }

        intermediate->Unmap(0, nullptr);

        // Now issue CopyTextureRegion for each subresource
        for (UINT i = 0; i < numSubresources; ++i) {
            D3D12_TEXTURE_COPY_LOCATION dstLoc = {};
            dstLoc.pResource = destResource;
            dstLoc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            dstLoc.SubresourceIndex = i + firstSubresource;

            D3D12_TEXTURE_COPY_LOCATION srcLoc = {};
            srcLoc.pResource = intermediate;
            srcLoc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
            srcLoc.PlacedFootprint = layouts[i];

            cmdList->CopyTextureRegion(&dstLoc, 0, 0, 0, &srcLoc, nullptr);
        }

        return requiredSize;
    }
}