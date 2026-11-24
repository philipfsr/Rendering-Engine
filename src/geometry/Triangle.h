#pragma once
#include "scene/Material.h"
#include <cstdint>

struct Triangle {
    std::uint32_t a, b, c;
    Material material;
};