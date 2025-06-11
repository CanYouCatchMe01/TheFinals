#include "windows_internal.h"
#include "render.h"
#include <thread>
#include <bitset>

int client_width = 800;
int client_height = 800;

int mouse_velocity_x = 0;
int mouse_velocity_y = 0;
float delta_time = 0.0f;

std::bitset<256> key_states;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
        case WM_KEYDOWN:
        {
            key_states[wParam] = true;
        }
        break;
        case WM_KEYUP:
        {
            key_states[wParam] = false;
        }
        break;
        case WM_SIZE:
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            client_width = rect.right - rect.left;
            client_height = rect.bottom - rect.top;

            if (render::enabled) {
                render::resize(client_width, client_height);
            }
        }
        break;
        case WM_INPUT: {
            RAWINPUT raw_input;
            UINT raw_input_size = sizeof(raw_input);
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &raw_input, &raw_input_size, sizeof(RAWINPUTHEADER));
            if (raw_input.header.dwType == RIM_TYPEMOUSE) {
                // Handle mouse input here
                // For example, you can process raw_input.data.mouse
                mouse_velocity_x += raw_input.data.mouse.lLastX;
                mouse_velocity_y += raw_input.data.mouse.lLastY;
            }
        }
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void game_thread() {
    while (true) {
        render::render(client_width, client_height);
    }
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
    RECT desired_rect = { 0, 0, client_width, client_height };
    AdjustWindowRect(&desired_rect, WS_OVERLAPPEDWINDOW, false);
    int window_width = desired_rect.right - desired_rect.left;
    int window_height = desired_rect.bottom - desired_rect.top;

    // Create a window
    HWND hwnd = CreateWindow(wc.lpszClassName, L"DirectX 12 Triangle", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, window_width, window_height, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hwnd, nCmdShow);

    render::setup(client_width, client_height, hwnd);

    RAWINPUTDEVICE raw_input_device = {};
    raw_input_device.usUsagePage = 0x01; // Generic Desktop Controls
    raw_input_device.usUsage = 0x02; // Mouse
    raw_input_device.dwFlags = 0;
    raw_input_device.hwndTarget = hwnd;
    BOOL ok = RegisterRawInputDevices(&raw_input_device, 1, sizeof(RAWINPUTDEVICE));

    //std::thread t1(game_thread);

    using Clock = std::chrono::high_resolution_clock;
    auto lastTime = Clock::now();

    bool running = true;
    while (running) {
        mouse_velocity_x = 0;
        mouse_velocity_y = 0;

        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        auto now = Clock::now();
        std::chrono::duration<float> deltaTime = now - lastTime;
        lastTime = now;

        delta_time = deltaTime.count();

        render::render(client_width, client_height);
    }
}