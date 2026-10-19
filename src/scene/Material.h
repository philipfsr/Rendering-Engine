#pragma once

#include "geometry/Vec3D.h"

struct Material {

    Vec3D albedo;
    float roughness;
    float metallic;
    Vec3D emissionColor;
    float emissionStrength;

};