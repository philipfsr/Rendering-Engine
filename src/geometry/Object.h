#pragma once

#include "Vertex.h"
#include "Triangle.h"
#include "Vec3D.h"

#include <vector>

struct Object {

    float x,y,z;

    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

    void translate(float x, float y, float z);
    void translate(Vec3D vec);
    void scale(float x, float y, float z);
    void scale(Vec3D vec);
};