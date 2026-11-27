#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#include <cstdint>
#include <iostream>
#include "MetalRenderer.h"
#include "geometry/Triangle.h"
#include "scene/Material.h"

static CAMetalLayer* layer;
static id<MTLCommandQueue> cmdQueue;
id<MTLDevice> device;
//id<MTLBuffer> triangleVertexBuffer;
id<MTLBuffer> vertexBuffer;
id<MTLBuffer> triangleBuffer;
id<MTLComputePipelineState> pipelineState;

std::vector<Vertex> vertices;
std::vector<Triangle> triangles;


bool initializeMetal(GLFWwindow* window, Scene* scene) {

    device = MTLCreateSystemDefaultDevice();
    if(device == nullptr) {
        return false;
    }

    NSWindow* nativeWindow = glfwGetCocoaWindow(window);
    NSView* view = [nativeWindow contentView];

    layer = [CAMetalLayer layer];
    layer.device = device;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;

    cmdQueue = [device newCommandQueue];
    if(cmdQueue == nil) {return false;}

    id<MTLLibrary> library = [device newDefaultLibrary];

    if (library == nil) {
        NSLog(@"No Metal-Shader-Library found");
        return false;
    }
    std::cout << "Loading Shaders\n";
    //id<MTLFunction> vertexShader = [library newFunctionWithName:@"vertexShader"];
    //id<MTLFunction> fragmentShader = [library newFunctionWithName:@"fragmentShader"];
    id<MTLFunction> computeShader = [library newFunctionWithName:@"computeShader"];

    if(computeShader == nil){
        NSLog(@"Could not create the compute shader");
        return false;
    }

    //if(fragmentShader == nil || vertexShader == nil) {return false;}

    MTLRenderPipelineDescriptor* pipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineDescriptor.label = @"Triangle Renderer";
    //pipelineDescriptor.vertexFunction = vertexShader;
    //pipelineDescriptor.fragmentFunction = fragmentShader;
    if(pipelineDescriptor == nil) {return false;}
    MTLPixelFormat pixelFormat = layer.pixelFormat;
    pipelineDescriptor.colorAttachments[0].pixelFormat = pixelFormat;

    NSError* error = nil;
    pipelineState = [device newComputePipelineStateWithFunction:computeShader error:&error];

    if(pipelineState == nil) {
        NSLog(@"Could not create compute-pipeline: %@", error);
        return false;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    layer.drawableSize = CGSizeMake(width, height);

    [view setWantsLayer:YES];
    [view setLayer:layer];

    vertices.clear();
    triangles.clear();

    for(const Object& object : scene->objects) {
        uint32_t offset = vertices.size();

        for(const Vertex& vertex : object.vertices) {
            vertices.push_back(vertex);
        }

        for(Triangle triangle : object.triangles) {
            triangles.push_back(Triangle{triangle.a + offset, triangle.b + offset, triangle.c + offset, triangle.material});
        }
    }

    vertexBuffer = [
        device
        newBufferWithBytes:vertices.data()
        length:vertices.size() * sizeof(Vertex)
        options:MTLResourceStorageModeShared
    ];

    triangleBuffer = [
        device
        newBufferWithBytes:triangles.data()
        length:triangles.size() * sizeof(Triangle)
        options:MTLResourceStorageModeShared
    ];

    if(vertexBuffer == nil || triangleBuffer == nil) {return false;}

    return true;
}

void renderMetalFrame(GLFWwindow* window, Scene* scene) {

    if(scene->objects.empty()) {return;}

    const auto& vertices = scene->objects[0].vertices;
    if(vertices.empty()) {return;}

    /*triangleVertexBuffer = [device newBufferWithBytes:vertices.data()
                                    length:vertices.size() * sizeof(Vertex)
                                    options:MTLResourceStorageModeShared];
    */
    @autoreleasepool { 

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        if(width <= 0 || height <= 0) {
            return;
        }

        CGSize size = CGSizeMake(width, height);
        if(!CGSizeEqualToSize(layer.drawableSize, size)) {
            layer.drawableSize = size;
        }

        id<CAMetalDrawable> drawable = [layer nextDrawable];
        if(drawable == nil) {return;}

        id<MTLCommandBuffer> cmdBuffer = [cmdQueue commandBuffer];

        MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
        pass.colorAttachments[0].texture = drawable.texture;
        pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        pass.colorAttachments[0].clearColor = MTLClearColorMake(0.1, 0.2, 0.8, 1.0);
        pass.colorAttachments[0].storeAction = MTLStoreActionStore;

        id<MTLRenderCommandEncoder> encoder = [cmdBuffer renderCommandEncoderWithDescriptor:pass];
        [encoder endEncoding];

        [cmdBuffer presentDrawable:drawable];
        [cmdBuffer commit];
    }
}