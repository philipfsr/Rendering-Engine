#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#include "MetalRenderer.h"

static CAMetalLayer* layer;
static id<MTLCommandQueue> cmdQueue;

bool initializeMetal(GLFWwindow* window) {

    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    if(device == nullptr) {
        return false;
    }

    NSWindow* nativeWindow = glfwGetCocoaWindow(window);
    NSView* view = [nativeWindow contentView];

    layer = [CAMetalLayer layer];
    layer.device = device;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;

    cmdQueue = [device newCommandQueue];
    if(cmdQueue == nil) {
        return false;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    layer.drawableSize = CGSizeMake(width, height);

    [view setWantsLayer:YES];
    [view setLayer:layer];

    return true;
}

void renderMetalFrame(GLFWwindow* window, Scene scene) {
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
        if(drawable == nil) {
            return;
        }

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