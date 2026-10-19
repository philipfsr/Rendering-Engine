#pragma once

#include "Camera.h"
#include "geometry/Object.h"

struct Scene {

    Camera camera;
    std::vector<Object> objects;

};