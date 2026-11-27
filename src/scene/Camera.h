#pragma once

#include "geometry/Vec3D.h"

struct Camera {

    Vec3D origin;
    Vec3D facing;
    Vec3D up;
    Vec3D right;
    float fov;
};