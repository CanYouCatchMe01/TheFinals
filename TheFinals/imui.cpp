#include "imui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx12.h"
#include "render.h"
#include "dx12_heap_allocator.h"
#include "game.h"

namespace imui {
    void SrvDescriptorAllocFn(ImGui_ImplDX12_InitInfo *info, D3D12_CPU_DESCRIPTOR_HANDLE *out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE *out_gpu_desc_handle) {
        size_t srv_allocated_pos = dx12_heap_allocator::malloc(render::cbv_srv_uav_heap_allocator, 1);

        const UINT increment_srv = render::device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        {
            D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle_srv = render::cbv_srv_uav_heap->GetCPUDescriptorHandleForHeapStart();
            cpu_handle_srv.ptr += increment_srv * srv_allocated_pos;
            out_cpu_desc_handle->ptr = cpu_handle_srv.ptr;
        }
        {
            D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle_srv = render::cbv_srv_uav_heap->GetGPUDescriptorHandleForHeapStart();
            gpu_handle_srv.ptr += increment_srv * srv_allocated_pos;
            out_gpu_desc_handle->ptr = gpu_handle_srv.ptr;
        }
    }

    void SrvDescriptorFreeFn(ImGui_ImplDX12_InitInfo *info, D3D12_CPU_DESCRIPTOR_HANDLE cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE gpu_desc_handle) {
        const UINT increment_srv = render::device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

        size_t srv_allocated_pos = (size_t)((cpu_desc_handle.ptr - render::cbv_srv_uav_heap->GetCPUDescriptorHandleForHeapStart().ptr) / increment_srv);
        dx12_heap_allocator::free(render::cbv_srv_uav_heap_allocator, srv_allocated_pos, 1);
    }

    void setup() {
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->AddFontDefault();

        ImGui_ImplWin32_Init(game::hwnd);

        ImGui_ImplDX12_InitInfo init_info;
        init_info.Device = render::device;
        init_info.CommandQueue = render::command_queue;
        init_info.NumFramesInFlight = FRAMES_IN_FLIGHT;
        init_info.RTVFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
        init_info.DSVFormat = DXGI_FORMAT_D32_FLOAT;
        init_info.SrvDescriptorHeap = render::cbv_srv_uav_heap;
        init_info.SrvDescriptorAllocFn = SrvDescriptorAllocFn;
        init_info.SrvDescriptorFreeFn = SrvDescriptorFreeFn;

        ImGui_ImplDX12_Init(&init_info);
    }

    void render() {
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ImGui::StyleColorsDark();
        ImGui::Begin("The Finals");
        ImGui::Text("Mouse velocity: %d, %d", game::mouse_velocity_x, game::mouse_velocity_y);
        ImGui::Text("Delta time: %.3f", game::delta_time);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        ImGui::End();
        ImGui::Render();
        ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), render::command_list);
    }
}