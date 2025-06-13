#pragma once
#include "dx12_heap_allocator.h"
#include <string>

namespace dx12_heap_allocator {
    size_t malloc(std::vector<bool> &bitset, size_t size) {
        if (size == 0) {
            return -1;
        }

        for (size_t i = 0; i < bitset.size() - size; i++) {
            bool free = true;
            size_t not_free_index = 0;
            for (size_t j = 0; j < size; j++) {
                if (bitset[i + j]) {
                    free = false;
                    not_free_index = j;
                    break;
                }
            }
            if (free) {
                for (size_t j = 0; j < size; j++) {
                    bitset[i + j] = true;
                }
                return i;
            }
            i += not_free_index;
        }
        // "Failed to allocate memory in heap allocator. Out of size"
        return -1;
    }
    void free(std::vector<bool> &bitset, size_t pos, size_t size) {
        if (pos + size > bitset.size()) {
            // "Failed to free memory in heap allocator. Out of size"
            return;
        }

        for (size_t i = pos; i < pos + size; i++) {
            bitset[i] = false;
        }
    }
}
