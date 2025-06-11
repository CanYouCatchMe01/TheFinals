#pragma once
#include "windows_internal.h"

struct ID3D12Device;

namespace render {
    extern bool enabled;
    extern ID3D12Device *device;

    void setup(unsigned int width, unsigned int height, HWND hwnd);
    void renderdoc_setup();
    void resize(unsigned int width, unsigned int height);
    void render(unsigned int width, unsigned int height);
}