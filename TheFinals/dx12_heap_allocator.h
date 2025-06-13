#pragma once
#include <vector>

namespace dx12_heap_allocator {
    size_t malloc(std::vector<bool> &heap_allocator, size_t size);
    void free(std::vector<bool> &heap_allocator, size_t pos, size_t size);
}
