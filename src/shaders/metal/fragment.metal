#include <metal_stdlib>
using namespace metal;

vertex float4 fragmentShader(float4 vertexOutPositions [[stage_in]]) {
    float4 outColor = float4(20.0f, 20.0f, 80.0f, 1.0f);

    return outColor;
}