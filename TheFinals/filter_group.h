#pragma once
#include <cstdint>

struct FilterGroup {
	enum Enum : uint32_t {
		Default = 1 << 0,
		Player = 1 << 1,
	};
};
