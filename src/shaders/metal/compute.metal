#include <metal_stdlib>
#include "geometry/Vec3D.h"

using namespace metal;

kernel void computeShader(Vec3D origin,
                        Vec3D facing,
                        float fov,
                        texture2d<float, access::write> output [[texture(0)]],
                        uint2 pixel [[thread_position_in_grid]]) {
    if(pixel.x >= output.get_width() ||
       pixel.y >= output.get_height()) {return;}

    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);



    output.write(color, pixel);
}