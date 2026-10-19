#pragma once

struct Vec3D {

    float x, y, z;

    Vec3D();
    Vec3D(float x, float y, float z);

    void translate(float x, float y, float z);
    void translate(Vec3D vec);
    Vec3D translated(float x, float y, float z) const;
    Vec3D translated(Vec3D vec) const;
    Vec3D cross(float x, float y, float z) const;
    Vec3D cross(Vec3D vec) const;
    void norm(float x, float y, float z);
    void norm(Vec3D vec);
    Vec3D normed(float x, float y, float z) const;
    Vec3D normed(Vec3D vec) const;
};