#pragma once

//Imgui dynamicly allocates textures, it says only 1 is used right now,
//but it safe to just allocate some extra space for future use.
#define IMGUI_MAX_SRV 64

namespace render {
    enum STATIC_SRV {
        MAIN_TEXTURE,
        IMGUI_SRV,
        EXTRA_1 = IMGUI_SRV + IMGUI_MAX_SRV,
        EXTRA_2,
        COUNT
    };
}
