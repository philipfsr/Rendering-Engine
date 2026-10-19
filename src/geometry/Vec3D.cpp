#include "Vec3D.h"

Vec3D::Vec3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vec3D::Vec3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec3D::translate(float x, float y, float z) {
    this->x += x;
    this->y += y;
    this->z += z;
}

void Vec3D::translate(Vec3D vec) {
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
}

Vec3D Vec3D::translated(float x, float y, float z) const {
    return Vec3D(this->x + x, this->y + y, this->z + z);
}

Vec3D Vec3D::translated(Vec3D vec) const {

}

Vec3D Vec3D::cross(float x, float y, float z) const {
    return Vec3D();
}

Vec3D Vec3D::cross(Vec3D vec) const {
    return Vec3D();
}

void Vec3D::norm(float x, float y, float z) {

}

void Vec3D::norm(Vec3D vec) {

}

Vec3D Vec3D::normed(float x, float y, float z) const {
    return Vec3D();
}

Vec3D Vec3D::normed(Vec3D vec) const {
    return Vec3D();
}