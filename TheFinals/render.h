#pragma once
#include "windows_internal.h"
#include <vector>

struct ID3D12Device;
struct ID3D12CommandQueue;
struct ID3D12GraphicsCommandList;
struct ID3D12DescriptorHeap;

#define FRAMES_IN_FLIGHT 1

namespace render {
    extern bool enabled;
    extern ID3D12Device *device;
    extern ID3D12CommandQueue *command_queue;
    extern ID3D12GraphicsCommandList *command_list;

    extern ID3D12DescriptorHeap *cbv_srv_uav_heap;

    void setup(unsigned int width, unsigned int height, HWND hwnd);
    void renderdoc_setup();
    void resize(unsigned int width, unsigned int height);
    void render(unsigned int width, unsigned int height);
}