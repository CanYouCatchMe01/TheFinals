#include "windows_internal.h"
#include "render.h"
#include <thread>
#include <bitset>
#include "imui.h"
#include "imgui/imgui_impl_win32.h"
#include "physics.h"
#include "scene.h"

namespace game {
    HWND hwnd = nullptr;
    int client_width = 800;
    int client_height = 800;

    int mouse_velocity_x = 0;
    int mouse_velocity_y = 0;
    float delta_time = 0.0f;

    std::bitset<256> key_states;
}

bool should_resize = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
        return true;  // ImGui has handled the message
    }

    switch (message) {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;

        case WM_KEYDOWN:
            game::key_states[wParam] = true;
        break;
        case WM_KEYUP:
            game::key_states[wParam] = false;
        break;

        // Mouse buttons
        case WM_LBUTTONDOWN:
            game::key_states[VK_LBUTTON] = true;
            break;
        case WM_LBUTTONUP:
            game::key_states[VK_LBUTTON] = false;
            break;

        case WM_RBUTTONDOWN:
            game::key_states[VK_RBUTTON] = true;
            break;
        case WM_RBUTTONUP:
            game::key_states[VK_RBUTTON] = false;
            break;

        case WM_MBUTTONDOWN:
            game::key_states[VK_MBUTTON] = true;
            break;
        case WM_MBUTTONUP:
            game::key_states[VK_MBUTTON] = false;
            break;

        case WM_SIZE:
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            game::client_width = rect.right - rect.left;
            game::client_height = rect.bottom - rect.top;

            should_resize = true;
        }
        break;
        case WM_INPUT: {
            RAWINPUT raw_input;
            UINT raw_input_size = sizeof(raw_input);
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &raw_input, &raw_input_size, sizeof(RAWINPUTHEADER));
            if (raw_input.header.dwType == RIM_TYPEMOUSE) {
                // Handle mouse input here
                // For example, you can process raw_input.data.mouse
                game::mouse_velocity_x += raw_input.data.mouse.lLastX;
                game::mouse_velocity_y += raw_input.data.mouse.lLastY;
            }
        }
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    render::renderdoc_setup();

    // Register a simple window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"DirectX12Triangle";
    RegisterClass(&wc);

    //the windows size is with the top bar
    RECT desired_rect = { 0, 0, game::client_width, game::client_height };
    AdjustWindowRect(&desired_rect, WS_OVERLAPPEDWINDOW, false);
    int window_width = desired_rect.right - desired_rect.left;
    int window_height = desired_rect.bottom - desired_rect.top;

    // Create a window
    game::hwnd = CreateWindow(wc.lpszClassName, L"DirectX 12 Triangle", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, window_width, window_height, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(game::hwnd, nCmdShow);

    RAWINPUTDEVICE raw_input_device = {};
    raw_input_device.usUsagePage = 0x01; // Generic Desktop Controls
    raw_input_device.usUsage = 0x02; // Mouse
    raw_input_device.dwFlags = 0;
    raw_input_device.hwndTarget = game::hwnd;
    BOOL ok = RegisterRawInputDevices(&raw_input_device, 1, sizeof(RAWINPUTDEVICE));

    scene::Scene scene;

    render::setup(game::client_width, game::client_height, game::hwnd);
    imui::setup();
    physics::setup();
    scene::setup(scene);

    //std::thread t1(game_thread);

    using Clock = std::chrono::high_resolution_clock;
    auto lastTime = Clock::now();

    bool running = true;
    while (running) {
        game::mouse_velocity_x = 0;
        game::mouse_velocity_y = 0;

        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (should_resize) {
            render::resize(scene.world, game::client_width, game::client_height);
            should_resize = false;
        }

        auto now = Clock::now();
        std::chrono::duration<float> deltaTime = now - lastTime;
        lastTime = now;

        game::delta_time = deltaTime.count();

        scene::update(scene);
        render::render(scene.world, game::client_width, game::client_height);
    }
}