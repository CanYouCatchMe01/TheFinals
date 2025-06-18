#pragma once
#include "windows_internal.h"
#include <bitset>

namespace game {
    extern HWND hwnd;
    extern int client_width;
    extern int client_height;

    extern int mouse_velocity_x;
    extern int mouse_velocity_y;
    extern float delta_time;

    bool is_key_held_down(int key);
    bool is_key_pressed(int key);
    bool is_key_released(int key);
}