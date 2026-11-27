#include <metal_stdlib>
#include "scene/Camera.h"
#include "geometry/Triangle.h"
#include "geometry/Vertex.h"

using namespace metal;

bool intersect(const device Triangle& triangle,
                const device Vertex* vertices,
                float3 origin,
                float3 direction,
                thread float& t) {
    t = 1.0f;
    return true;
}

void rotate(float angle, float3& axis, float cos, float sin, float3& ray) {
    ray = ray * cos + cross(axis, ray) * sin + axis * dot(axis, ray) * (1.0f - c);
}


float3 createCameraRay(constant Camera& camera, uint2 pixel, uint2 imgSize) {
    float3 facing = float3(camera.facing.x, camera.facing.y, camera.facing.z);
    float3 up = float3(camera.up.x, camera.up.y, camera.up.z);
    float3 right = float3(camera.right.x, camera.right.y, camera.right.z);

    float x = 2.0f * ((float(pixel.x) + 0.5f) / float(imgSize.x)) - 1.0f;
    float y = 1.0f - 2.0f * ((float(pixel.y) +0.5) / float(imgSize.y));

    float aspect = float(imgSize.x) / float(imgSize.y);
    float halfWidth = tan(camera.fov * (M_PI_F / 180.0f) *0.5f);
    float halfHeight = halfWidth / aspect;

    return normalize(facing + right * (x * halfWidth) + up * (y * halfHeight));
}

kernel void computeShader(const device Vertex* vertices [[buffer(0)]],
                        const device Triangle* triangles [[buffer(1)]],
                        constant Camera& camera [[buffer(2)]],
                        constant uint& trianglesSize [[buffer(3)]],
                        texture2d<float, access::write> output [[texture(0)]],
                        uint2 pixel [[thread_position_in_grid]]) {
    if(pixel.x >= output.get_width() ||
       pixel.y >= output.get_height()) {return;}

    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    //calculate camera ray:
    uint2 imgSize = uint2(output.get_width(), output.get_height());
    float3 camRay = createCameraRay(camera, pixel, imgSize);

    float tNearest = FLT_MAX;
    int nearest = -1;

    for (uint i = 0; i < trianglesSize; i++) {
        float t = FLT_MAX;

        if(!intersect(triangles[i], vertices, float3(camera.origin.x, camera.origin.y, camera.origin.z), camRay, t)) {
            continue;
        }

        if(t < tNearest) {
            tNearest = t;
            nearest = i;
        }
    }

    if(nearest >= 0) {
        color = float4(0.80f, 0.1f, 30.0f, 1.0f)
    }

    output.write(color, pixel);
}

