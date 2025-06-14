#define D3D_DEBUG 2 //0=None, 1=DX12Debug, 2=RenderDoc
#define D3D_DEBUG_BREAK 1 //0=off, 1=on

#include "render.h"
#include "render_internal.h"
#include <dxgi1_6.h>
#include "DDSTextureLoader.h"
#include <DirectXMath.h>
#include <sstream>
#include <fstream>
#include <map>
#include "dx12_helper.h"
#include "material.h"
#include <filesystem>
#include "renderdoc_app.h"
#include <bitset>
#include "game.h"
#include "imui.h"
#include "static_srv.h"

#pragma comment(lib, "dxgi.lib")

namespace render {
    struct Vertex {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT2 uv;
    };

    struct Model {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indicies;
    };

    struct Camera {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 rotation; // Quaternion
        DirectX::XMMATRIX projection;
    };

    bool enabled = false;
    ID3D12Device *device = nullptr;
    ID3D12CommandQueue *command_queue = nullptr;
    ID3D12CommandAllocator *command_allocator = nullptr;
    ID3D12GraphicsCommandList *command_list = nullptr;

    ID3D12Resource *depth_stencil_buffer = nullptr;
    IDXGISwapChain3 *swap_chain = nullptr;
    ID3D12Resource *swap_chain_resources[2] = { nullptr, nullptr };

    ID3D12Fence *fence = nullptr;
    UINT64 fence_value = 0;
    HANDLE fence_event;

    ID3D12DescriptorHeap *rtv_heap = nullptr;
    ID3D12DescriptorHeap *cbv_srv_uav_heap = nullptr;
    ID3D12DescriptorHeap *dsv_heap = nullptr;

    Model cube_model = {};
    ID3D12Resource *vertex_buffer = nullptr; //fast. GPU access only
    ID3D12Resource *index_buffer = nullptr; //fast. GPU access only
    unsigned int triangle_angle = 0;

    ID3D12Resource *frame_constants = nullptr;
    ID3D12Resource *frame_constants_upload = nullptr;
    ID3D12Resource *object_buffer = nullptr;
    ID3D12Resource *object_buffer_upload = nullptr;
    Camera camera = {};

    std::string get_renderdoc_dll_path() {
        char *value = NULL;
        size_t len = 0;
        errno_t err = _dupenv_s(&value, &len, "ProgramFiles");

        if (value != nullptr) {
            std::filesystem::path renderdoc_path = std::filesystem::path(value) / "RenderDoc" / "renderdoc.dll";

            if (std::filesystem::exists(renderdoc_path)) {
                return renderdoc_path.string();
            }
        }

        return "renderdoc.dll";
    }

#if D3D_DEBUG == 2
    void renderdoc_setup() {
        RENDERDOC_API_1_6_0 *rdoc_api = NULL;

        std::string renderdoc_path = get_renderdoc_dll_path();
        HMODULE loadModule = LoadLibraryA(renderdoc_path.c_str());
        if (!loadModule) return;
        pRENDERDOC_GetAPI RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)GetProcAddress(loadModule, "RENDERDOC_GetAPI");
        int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_6_0, (void **)&rdoc_api);
        if (ret != 1) return;
        RENDERDOC_InputButton capture_keys[2] = { RENDERDOC_InputButton::eRENDERDOC_Key_PrtScrn, RENDERDOC_InputButton::eRENDERDOC_Key_F11 };
        rdoc_api->SetCaptureKeys(capture_keys, 2);
    }
#else
    void renderdoc_setup() {
    }
#endif

    Model load_model_from_obj(const std::string &path) {
        std::ifstream file(path);  // Open the file

        if (!file.is_open()) {
            return {};
        }

        Model model;
        std::vector<DirectX::XMFLOAT3> temp_positions;
        std::vector<DirectX::XMFLOAT2> temp_uvs;
        std::vector<DirectX::XMFLOAT3> temp_normals;
        std::map<std::tuple<unsigned int, unsigned int, unsigned int>, unsigned int> index_map;
        std::vector<unsigned int> temp_face_indices;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);

            std::string prefix;
            ss >> prefix;

            if (prefix == "v") { //vertex position
                DirectX::XMFLOAT3 position;
                ss >> position.x >> position.y >> position.z;
                temp_positions.push_back(position);
            } else if (prefix == "vn") { //vertex normal
                DirectX::XMFLOAT3 normal;
                ss >> normal.x >> normal.y >> normal.z;
                temp_normals.push_back(normal);
            } else if (prefix == "vt") { //vertex normal
                DirectX::XMFLOAT2 uv;
                ss >> uv.x >> uv.y;
                temp_uvs.push_back(uv);
            } else if (prefix == "f") {
                temp_face_indices.clear();

                std::string vertexindex_slashslash_normalindex;
                while (ss >> vertexindex_slashslash_normalindex) {
                    size_t slash_pos_0 = vertexindex_slashslash_normalindex.find("/");
                    size_t slash_pos_1 = vertexindex_slashslash_normalindex.find("/", slash_pos_0 + 1);

                    std::string vertex_index_str = vertexindex_slashslash_normalindex.substr(0, slash_pos_0);
                    std::string uv_index_str = vertexindex_slashslash_normalindex.substr(slash_pos_0 + 1, slash_pos_1 - slash_pos_0 - 1);
                    std::string normal_index_str = vertexindex_slashslash_normalindex.substr(slash_pos_1 + 1);
                    unsigned int vertex_index = std::stoi(vertex_index_str) - 1;
                    unsigned int uv_index = std::stoi(uv_index_str) - 1;
                    unsigned int normal_index = std::stoi(normal_index_str) - 1;

                    // Check if the vertex and normal index pair already exists in the map
                    auto it = index_map.find({ vertex_index, uv_index, normal_index });

                    if (it != index_map.end()) {
                        temp_face_indices.push_back(it->second);
                    } else {
                        // If it doesn't exist, create a new vertex and add it to the model
                        Vertex vertex;
                        vertex.position = temp_positions[vertex_index];
                        vertex.normal = temp_normals[normal_index];
                        vertex.uv = temp_uvs[uv_index];
                        unsigned int new_index = static_cast<unsigned int>(model.vertices.size());
                        model.vertices.push_back(vertex);
                        // Store the new index in the map
                        index_map[{ vertex_index, uv_index, normal_index }] = new_index;
                        temp_face_indices.push_back(new_index);
                    }
                }

                for (int i = 0; i < (int)temp_face_indices.size() - 2; i++) {
                    model.indicies.push_back(temp_face_indices[0]);
                    model.indicies.push_back(temp_face_indices[i + 1]);
                    model.indicies.push_back(temp_face_indices[i + 2]);
                }
            }
        }
        file.close();  // Close the file
        return model;
    }

    void create_depth_buffer(unsigned int width, unsigned int height) {
        if (depth_stencil_buffer) {
            depth_stencil_buffer->Release();
            depth_stencil_buffer = nullptr;
        }

        D3D12_HEAP_PROPERTIES heap_properties = {};
        heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
        heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        heap_properties.CreationNodeMask = 1;
        heap_properties.VisibleNodeMask = 1;

        D3D12_RESOURCE_DESC resource_desc = {};
        resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        resource_desc.Alignment = 0;
        resource_desc.Width = width;
        resource_desc.Height = height;
        resource_desc.DepthOrArraySize = 1;
        resource_desc.MipLevels = 1;
        resource_desc.Format = DXGI_FORMAT_D32_FLOAT;
        resource_desc.SampleDesc.Count = 1;
        resource_desc.SampleDesc.Quality = 0;
        resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
        resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

        D3D12_CLEAR_VALUE clear_value = {};
        clear_value.Format = DXGI_FORMAT_D32_FLOAT;
        clear_value.DepthStencil.Depth = 0.0f;
        clear_value.DepthStencil.Stencil = 0;

        HRESULT hr = device->CreateCommittedResource(
            &heap_properties,
            D3D12_HEAP_FLAG_NONE,
            &resource_desc,
            D3D12_RESOURCE_STATE_DEPTH_WRITE,
            &clear_value,
            IID_PPV_ARGS(&depth_stencil_buffer));

        D3D12_CPU_DESCRIPTOR_HANDLE dsv_handle(dsv_heap->GetCPUDescriptorHandleForHeapStart());
        device->CreateDepthStencilView(depth_stencil_buffer, nullptr, dsv_handle);
    }

    void setup(unsigned int width, unsigned int height, HWND hwnd) {
#if D3D_DEBUG_BREAK == 1
    {
#pragma message("WARNING: DX12 DEBUG ENABLED, CAN BE SLOW")
        ID3D12Debug1 *debug_controller1 = nullptr;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller1)))) {
            debug_controller1->EnableDebugLayer();
            debug_controller1->SetEnableGPUBasedValidation(TRUE);
            debug_controller1->Release();
        }
    }
#endif

        //The device is like a virtual representation of the GPU
        HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

#if D3D_DEBUG == 1
        {
#pragma message("WARNING: DX12 DEBUG ENABLED, CAN BE SLOW")
            ID3D12InfoQueue *infoQueue = nullptr;
            if (SUCCEEDED(device->QueryInterface(__uuidof(ID3D12InfoQueue), (void **)&infoQueue))) {
                infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
                infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
                infoQueue->Release();
            }
        }
#endif

        //command queue decides which order the command lists should execute. In our case, we only have one command list.
        D3D12_COMMAND_QUEUE_DESC queue_desc = {};
        queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        hr = device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&command_queue));

        //command allocator is used to allocate memory on the GPU for commands
        hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator));
        hr = command_allocator->Reset();

        //command list is used to store a list of commands that we want to execute on the GPU
        hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator, nullptr, IID_PPV_ARGS(&command_list));
        hr = command_list->Close();

        //fence is used to synchronize the CPU with the GPU, so they don't touch the same memory at the same time
        hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
        fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        //memory descriptor heap to store render target views(RTV). Descriptor describes how to interperate resource memory.
        D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {};
        rtv_heap_desc.NumDescriptors = 2;
        rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        hr = device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&rtv_heap));

        //store extra data for texture to use in shaders
        D3D12_DESCRIPTOR_HEAP_DESC cbv_srv_uav_heap_desc = {};
        cbv_srv_uav_heap_desc.NumDescriptors = STATIC_SRV::COUNT;
        cbv_srv_uav_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        cbv_srv_uav_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        hr = device->CreateDescriptorHeap(&cbv_srv_uav_heap_desc, IID_PPV_ARGS(&cbv_srv_uav_heap));

        //memory descriptor heap to store render target views(DSV). Descriptor describes how to interperate resource memory.
        D3D12_DESCRIPTOR_HEAP_DESC dsv_heap_desc = {};
        dsv_heap_desc.NumDescriptors = 1;
        dsv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        hr = device->CreateDescriptorHeap(&dsv_heap_desc, IID_PPV_ARGS(&dsv_heap));

        //helper object to create a swap chain
        IDXGIFactory4 *factory = nullptr;
        hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));

        //create swap chain
        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        swap_chain_desc.BufferCount = 2;
        swap_chain_desc.BufferDesc.Width = width;
        swap_chain_desc.BufferDesc.Height = height;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swap_chain_desc.OutputWindow = hwnd;
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.Windowed = TRUE;
        swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

        IDXGISwapChain *temp_swap_chain = nullptr;
        hr = factory->CreateSwapChain(command_queue, &swap_chain_desc, &temp_swap_chain);

        //cast the swap chain to IDXGISwapChain3 to leverage the latest features
        hr = temp_swap_chain->QueryInterface(IID_PPV_ARGS(&swap_chain));
        temp_swap_chain->Release();
        temp_swap_chain = nullptr;

        UINT rtv_increment_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        {
            D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle(rtv_heap->GetCPUDescriptorHandleForHeapStart());
            for (UINT i = 0; i < 2; i++) {
                hr = swap_chain->GetBuffer(i, IID_PPV_ARGS(&swap_chain_resources[i]));

                device->CreateRenderTargetView(swap_chain_resources[i], nullptr, rtv_handle);
                rtv_handle.ptr += rtv_increment_size;
            }
        }

        create_depth_buffer(width, height);
        material::setup();

        cube_model = load_model_from_obj("cube2.obj");
        ID3D12Resource *vertex_buffer_upload = nullptr; //slow. CPU and GPU access
        ID3D12Resource *index_buffer_upload = nullptr; //slow. CPU and GPU access
        ID3D12Resource *texture_resource = nullptr; //fast. GPU access only
        ID3D12Resource *texture_resource_upload = nullptr; //slow. CPU and GPU access

        std::unique_ptr<uint8_t[]> dds_data;
        std::vector<D3D12_SUBRESOURCE_DATA> subresources;
        DirectX::LoadDDSTextureFromFile(
            device,
            L"brick512.dds",
            &texture_resource, //create black texture, we will upload its data later
            dds_data,
            subresources
        );

        D3D12_CPU_DESCRIPTOR_HANDLE cbv_srv_uav_handle = cbv_srv_uav_heap->GetCPUDescriptorHandleForHeapStart();
        cbv_srv_uav_handle.ptr += render::STATIC_SRV::MAIN_TEXTURE * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        device->CreateShaderResourceView(texture_resource, nullptr, cbv_srv_uav_handle);

        //create vertex and index buffer
        {
            //heap properties
            D3D12_HEAP_PROPERTIES heap_properties = {};
            heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
            heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
            heap_properties.CreationNodeMask = 1;
            heap_properties.VisibleNodeMask = 1;

            D3D12_HEAP_PROPERTIES heap_properties_upload = heap_properties;
            heap_properties_upload.Type = D3D12_HEAP_TYPE_UPLOAD;

            //resource description
            D3D12_RESOURCE_DESC resource_desc = {};
            resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            resource_desc.Alignment = 0;
            resource_desc.Width = sizeof(Vertex) * cube_model.vertices.size();
            resource_desc.Height = 1;
            resource_desc.DepthOrArraySize = 1;
            resource_desc.MipLevels = 1;
            resource_desc.Format = DXGI_FORMAT_UNKNOWN;
            resource_desc.SampleDesc.Count = 1;
            resource_desc.SampleDesc.Quality = 0;
            resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
            resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

            //vertex
            hr = device->CreateCommittedResource(
                &heap_properties,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_COMMON,
                nullptr,
                IID_PPV_ARGS(&vertex_buffer)
            );

            hr = device->CreateCommittedResource(
                &heap_properties_upload,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&vertex_buffer_upload)
            );

            //index
            resource_desc.Width = sizeof(unsigned int) * cube_model.indicies.size();
            hr = device->CreateCommittedResource(
                &heap_properties,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_COMMON,
                nullptr,
                IID_PPV_ARGS(&index_buffer)
            );

            hr = device->CreateCommittedResource(
                &heap_properties_upload,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&index_buffer_upload)
            );

            //texture upload
            resource_desc.Width = dx12_helper::MyGetRequiredIntermediateSize(texture_resource, 0, (UINT)subresources.size());
            hr = device->CreateCommittedResource(
                &heap_properties_upload,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&texture_resource_upload)
            );

            resource_desc.Width = sizeof(DirectX::XMFLOAT4X4);
            hr = device->CreateCommittedResource(
                &heap_properties,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_COMMON,
                nullptr,
                IID_PPV_ARGS(&frame_constants)
            );

            hr = device->CreateCommittedResource(
                &heap_properties_upload,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&frame_constants_upload)
            );

            resource_desc.Width = sizeof(DirectX::XMFLOAT4X4);
            hr = device->CreateCommittedResource(
                &heap_properties,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_COMMON,
                nullptr,
                IID_PPV_ARGS(&object_buffer)
            );

            hr = device->CreateCommittedResource(
                &heap_properties_upload,
                D3D12_HEAP_FLAG_NONE,
                &resource_desc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&object_buffer_upload)
            );


            //copy data from CPU to the upload buffers
            void *vertex_mapped_data = nullptr;
            hr = vertex_buffer_upload->Map(0, nullptr, &vertex_mapped_data);
            memcpy(vertex_mapped_data, cube_model.vertices.data(), sizeof(Vertex) * cube_model.vertices.size());
            vertex_buffer_upload->Unmap(0, nullptr);

            void *index_mapped_data = nullptr;
            hr = index_buffer_upload->Map(0, nullptr, &index_mapped_data);
            memcpy(index_mapped_data, cube_model.indicies.data(), sizeof(unsigned int) * cube_model.indicies.size());
            index_buffer_upload->Unmap(0, nullptr);

            //Record commands to copy the data from the upload buffer to the fast default buffer
            hr = command_allocator->Reset();
            hr = command_list->Reset(command_allocator, nullptr);

            //barrier just for vertex and index buffers
            {
                D3D12_RESOURCE_BARRIER barrier[4] = {};
                barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier[0].Transition.pResource = vertex_buffer;
                barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
                barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
                barrier[0].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

                barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier[1].Transition.pResource = index_buffer;
                barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
                barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
                barrier[1].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

                barrier[2].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier[2].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier[2].Transition.pResource = frame_constants;
                barrier[2].Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
                barrier[2].Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
                barrier[2].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

                barrier[3].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier[3].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier[3].Transition.pResource = object_buffer;
                barrier[3].Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
                barrier[3].Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
                barrier[3].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

                command_list->ResourceBarrier(_countof(barrier), barrier);
            }

            //copy the data from upload to the fast default buffer
            command_list->CopyResource(vertex_buffer, vertex_buffer_upload);
            command_list->CopyResource(index_buffer, index_buffer_upload);
            dx12_helper::MyUpdateSubresources(command_list, texture_resource, texture_resource_upload, 0, 0, (UINT)subresources.size(), subresources.data());

            //barrier for vertex, index and texture
            {
                D3D12_RESOURCE_BARRIER barrier[3] = {};
                barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier[0].Transition.pResource = vertex_buffer;
                barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
                barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
                barrier[0].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

                barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier[1].Transition.pResource = index_buffer;
                barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
                barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_INDEX_BUFFER;
                barrier[1].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

                barrier[2].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier[2].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barrier[2].Transition.pResource = texture_resource;
                barrier[2].Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
                barrier[2].Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
                barrier[2].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

                command_list->ResourceBarrier(_countof(barrier), barrier);
            }

            hr = command_list->Close();

            ID3D12CommandList *command_lists[] = { command_list };
            command_queue->ExecuteCommandLists(1, command_lists);

            // Wait on the CPU for the GPU frame to finish
            const UINT64 current_fence_value = ++fence_value;
            hr = command_queue->Signal(fence, current_fence_value);

            if (fence->GetCompletedValue() < current_fence_value) {
                hr = fence->SetEventOnCompletion(current_fence_value, fence_event);
                WaitForSingleObject(fence_event, INFINITE);
            }

            camera.position = DirectX::XMFLOAT3(0, 0, -1);
            DirectX::XMStoreFloat4(&camera.rotation, DirectX::XMQuaternionIdentity());
            
            constexpr float fov_y = DirectX::XMConvertToRadians(90.0f);
            float aspect_ratio = float(width) / float(height);
            float near_z = 1000.0f; //reverse depth
            float far_z = 0.1f;
            camera.projection = DirectX::XMMatrixPerspectiveFovLH(fov_y, aspect_ratio, near_z, far_z);

            enabled = true;

//#if 1
//            RECT desktop;
//            GetWindowRect(GetDesktopWindow(), &desktop);
//            int width = desktop.right;
//            int height = desktop.bottom;
//
//            SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP);
//            SetWindowPos(hwnd, HWND_TOP,
//                0, 0, width, height,
//                SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_SHOWWINDOW);
//#else
//
//            // fullscreen window style
//            SetWindowLongPtr(hwnd, GWL_STYLE, 0);
//            SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
//
//            SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
//            ShowWindow(hwnd, SW_SHOWMAXIMIZED);
//#endif

//#if 1
//            // Original style for normal windowed mode
//            LONG_PTR style = WS_OVERLAPPEDWINDOW;
//
//            // Restore the style
//            SetWindowLongPtr(hwnd, GWL_STYLE, style);
//
//            // Restore window position and size (example: 1280x720 at 100, 100)
//            int windowedX = 100;
//            int windowedY = 100;
//            int windowedWidth = 1280;
//            int windowedHeight = 720;
//
//            SetWindowPos(hwnd, HWND_NOTOPMOST,
//                windowedX, windowedY,
//                windowedWidth, windowedHeight,
//                SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOOWNERZORDER | SWP_NOZORDER);
//#else
//            // Restore standard overlapped window style (title bar, borders, etc.)
//            SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
//            SetWindowLongPtr(hwnd, GWL_EXSTYLE, 0); // Or whatever it was before fullscreen
//
//            // Restore to a desired window size and position (e.g. 1280x720 at 100,100)
//            int windowedX = 100;
//            int windowedY = 100;
//            int windowedWidth = 1280;
//            int windowedHeight = 720;
//
//            SetWindowPos(hwnd, HWND_NOTOPMOST,
//                windowedX, windowedY,
//                windowedWidth, windowedHeight,
//                SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOOWNERZORDER);
//#endif
            
        }
    }

    void resize(unsigned int width, unsigned int height) {
        create_depth_buffer(width, height);

        for (UINT i = 0; i < 2; ++i) {
            swap_chain_resources[i]->Release();
            swap_chain_resources[i] = nullptr;
        }

        swap_chain->ResizeBuffers(2, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING);
        //swap_chain->ResizeBuffers(2, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
        UINT rtv_increment_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        {
            D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle(rtv_heap->GetCPUDescriptorHandleForHeapStart());
            for (UINT i = 0; i < 2; i++) {
                HRESULT hr = swap_chain->GetBuffer(i, IID_PPV_ARGS(&swap_chain_resources[i]));

                device->CreateRenderTargetView(swap_chain_resources[i], nullptr, rtv_handle);
                rtv_handle.ptr += rtv_increment_size;
            }
        }

        constexpr float fov_y = DirectX::XMConvertToRadians(90.0f);
        float aspect_ratio = float(width) / float(height);
        float near_z = 1000.0f; //reverse depth
        float far_z = 0.1f;
        camera.projection = DirectX::XMMatrixPerspectiveFovLH(fov_y, aspect_ratio, near_z, far_z);
    }

    void render(unsigned int width, unsigned int height) {

        if (game::key_states[VK_RBUTTON]) {
            // Get the client rect (in client coordinates)
            RECT clientRect;
            GetClientRect(game::hwnd, &clientRect);

            // Calculate the center of the client area
            int centerX = (clientRect.right - clientRect.left) / 2;
            int centerY = (clientRect.bottom - clientRect.top) / 2;

            // Convert the center point to screen coordinates
            POINT pt = { centerX, centerY };
            ClientToScreen(game::hwnd, &pt);

            // Move the cursor to the center of the client area
            SetCursorPos(pt.x, pt.y);

            while (ShowCursor(FALSE) >= 0);
        } else {
            while (ShowCursor(TRUE) < 0);
        }


        // Record commands to draw a triangle
        HRESULT hr = command_allocator->Reset();
        hr = command_list->Reset(command_allocator, nullptr);

        command_list->SetDescriptorHeaps(1, &cbv_srv_uav_heap);

        UINT back_buffer_index = swap_chain->GetCurrentBackBufferIndex();

        {
            D3D12_RESOURCE_BARRIER barrier[3] = {};
            barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier[0].Transition.pResource = swap_chain_resources[back_buffer_index];
            barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
            barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
            barrier[0].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

            barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier[1].Transition.pResource = frame_constants;
            barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
            barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
            barrier[1].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

            barrier[2].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier[2].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier[2].Transition.pResource = object_buffer;
            barrier[2].Transition.StateBefore = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
            barrier[2].Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
            barrier[2].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

            command_list->ResourceBarrier(_countof(barrier), barrier);
        }
        {
            DirectX::XMFLOAT2 cam_velocity = DirectX::XMFLOAT2(0, 0);
            if (game::key_states['D']) cam_velocity.x += 1.0f;
            if (game::key_states['A']) cam_velocity.x -= 1.0f;
            if (game::key_states['W']) cam_velocity.y += 1.0f;
            if (game::key_states['S']) cam_velocity.y -= 1.0f;

            float move_speed = 5.0f * game::delta_time;
            cam_velocity.x *= move_speed;
            cam_velocity.y *= move_speed;

            float rotation_speed = 0.01f;

            float mouse_velocity_speed_x = game::key_states[VK_RBUTTON] ? float(game::mouse_velocity_x) * rotation_speed : 0.0f;
            float mouse_velocity_speed_y = game::key_states[VK_RBUTTON] ? float(game::mouse_velocity_y) * rotation_speed : 0.0f;

            DirectX::XMVECTOR rot_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0, 1, 0, 0), mouse_velocity_speed_x);
            DirectX::XMVECTOR rot_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1, 0, 0, 0), mouse_velocity_speed_y);
            DirectX::XMVECTOR cam_rot = DirectX::XMVectorSet(camera.rotation.x, camera.rotation.y, camera.rotation.z, camera.rotation.w);
            cam_rot = DirectX::XMQuaternionMultiply(cam_rot, rot_x);
            cam_rot = DirectX::XMQuaternionMultiply(rot_y, cam_rot);
            DirectX::XMStoreFloat4(&camera.rotation, cam_rot);

            DirectX::XMVECTOR cam_right = DirectX::XMVector3Rotate(DirectX::XMVectorSet(1, 0, 0, 0), cam_rot);
            cam_right = DirectX::XMVectorMultiply(cam_right, DirectX::XMVectorSet(cam_velocity.x, cam_velocity.x, cam_velocity.x, 0));
            DirectX::XMVECTOR cam_forward = DirectX::XMVector3Rotate(DirectX::XMVectorSet(0, 0, 1, 0), cam_rot);
            cam_forward = DirectX::XMVectorMultiply(cam_forward, DirectX::XMVectorSet(cam_velocity.y, cam_velocity.y, cam_velocity.y, 0));

            camera.position.x += DirectX::XMVectorGetX(cam_right) + DirectX::XMVectorGetX(cam_forward);
            camera.position.y += DirectX::XMVectorGetY(cam_right) + DirectX::XMVectorGetY(cam_forward);
            camera.position.z += DirectX::XMVectorGetZ(cam_right) + DirectX::XMVectorGetZ(cam_forward);
            


            //frame constants
            DirectX::XMMATRIX pos_matrix = DirectX::XMMatrixTranslation(camera.position.x, camera.position.y, camera.position.z);
            DirectX::XMVECTOR rot = DirectX::XMLoadFloat4(&camera.rotation);
            DirectX::XMMATRIX rot_matrix = DirectX::XMMatrixRotationQuaternion(rot);

            DirectX::XMMATRIX world = rot_matrix * pos_matrix;
            DirectX::XMMATRIX view = DirectX::XMMatrixInverse(nullptr, world);
            DirectX::XMMATRIX view_proj = view * camera.projection;

            void *frame_mapped_data = nullptr;
            hr = frame_constants_upload->Map(0, nullptr, &frame_mapped_data);
            DirectX::XMFLOAT4X4 *frame_constants_data = (DirectX::XMFLOAT4X4 *)frame_mapped_data;
            DirectX::XMStoreFloat4x4(frame_constants_data, DirectX::XMMatrixTranspose(view_proj));
            frame_constants_upload->Unmap(0, nullptr);

            DirectX::XMMATRIX object_matrix = DirectX::XMMatrixTranslation(0,0,0);

            void *object_mapped_data = nullptr;
            hr = object_buffer_upload->Map(0, nullptr, &object_mapped_data);
            DirectX::XMFLOAT4X4 *object_constants_data = (DirectX::XMFLOAT4X4 *)object_mapped_data;
            DirectX::XMStoreFloat4x4(object_constants_data, DirectX::XMMatrixTranspose(object_matrix));
            object_buffer_upload->Unmap(0, nullptr);

            command_list->CopyResource(frame_constants, frame_constants_upload);
            command_list->CopyResource(object_buffer, object_buffer_upload);
        }
        {
            D3D12_RESOURCE_BARRIER barrier[2] = {};
            barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier[0].Transition.pResource = frame_constants;
            barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
            barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
            barrier[0].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

            barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier[1].Transition.pResource = object_buffer;
            barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
            barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
            barrier[1].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

            command_list->ResourceBarrier(_countof(barrier), barrier);
        }

        UINT rtv_increment_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle = rtv_heap->GetCPUDescriptorHandleForHeapStart();
        rtv_handle.ptr += back_buffer_index * rtv_increment_size;

        // Clear the render target
        float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
        command_list->ClearRenderTargetView(rtv_handle, clearColor, 0, nullptr);

        D3D12_CPU_DESCRIPTOR_HANDLE dsv_handle = dsv_heap->GetCPUDescriptorHandleForHeapStart();
        command_list->ClearDepthStencilView(dsv_handle, D3D12_CLEAR_FLAG_DEPTH, 0.0f, 0, 0, nullptr);

        // Set viewport and scissor
        D3D12_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 1.0f };
        D3D12_RECT scissor_rect = { 0, 0, LONG_MAX, LONG_MAX };
        command_list->RSSetViewports(1, &viewport);
        command_list->RSSetScissorRects(1, &scissor_rect);

        command_list->OMSetRenderTargets(1, &rtv_handle, FALSE, &dsv_handle);
        command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        command_list->SetGraphicsRootSignature(material::root_signature);
        command_list->SetPipelineState(material::pipeline_state);

        // Draw
        command_list->SetGraphicsRootConstantBufferView(0, frame_constants->GetGPUVirtualAddress());
        command_list->SetGraphicsRootConstantBufferView(1, object_buffer->GetGPUVirtualAddress());

        D3D12_GPU_DESCRIPTOR_HANDLE cbv_srv_uav_gpu_handle(cbv_srv_uav_heap->GetGPUDescriptorHandleForHeapStart());
        command_list->SetGraphicsRootDescriptorTable(2, cbv_srv_uav_gpu_handle); //texture

        D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view = {};
        vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
        vertex_buffer_view.StrideInBytes = sizeof(Vertex);
        vertex_buffer_view.SizeInBytes = sizeof(Vertex) * cube_model.vertices.size();
        command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);

        D3D12_INDEX_BUFFER_VIEW index_buffer_view = {};
        index_buffer_view.BufferLocation = index_buffer->GetGPUVirtualAddress();
        index_buffer_view.SizeInBytes = sizeof(unsigned int) * cube_model.indicies.size();
        index_buffer_view.Format = DXGI_FORMAT_R32_UINT;
        command_list->IASetIndexBuffer(&index_buffer_view);

        command_list->DrawIndexedInstanced(cube_model.indicies.size(), 1, 0, 0, 0);

        imui::render();

        {
            D3D12_RESOURCE_BARRIER barrier = {};
            barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier.Transition.pResource = swap_chain_resources[back_buffer_index];
            barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
            barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
            barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
            command_list->ResourceBarrier(1, &barrier);
        }

        hr = command_list->Close();

        ID3D12CommandList *command_lists[] = { command_list };
        command_queue->ExecuteCommandLists(1, command_lists);

        hr = swap_chain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
        //hr = swap_chain->Present(0, 0);

        // Wait on the CPU for the GPU frame to finish
        const UINT64 current_fence_value = ++fence_value;
        hr = command_queue->Signal(fence, current_fence_value);

        if (fence->GetCompletedValue() < current_fence_value) {
            hr = fence->SetEventOnCompletion(current_fence_value, fence_event);
            WaitForSingleObject(fence_event, INFINITE);
        }

        triangle_angle++;
    }
}