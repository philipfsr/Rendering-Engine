#pragma once
#include "scene/Material.h"
#include "geometry/Vertex.h"

struct Triangle {
    Vertex a, b, c;
    Material material;
};