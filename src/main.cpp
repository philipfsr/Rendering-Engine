#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>

#if defined(USE_METAL)
    #include "platform/macos/MetalRenderer.h"
#elif defined(USE_VULKAN)
    #include "platform/windows/VulkanRenderer.h"
#endif

#include "scene/Scene.h"

GLFWwindow* window;
int height, width;
Scene scene;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool initialize() {
    
    height = 480;
    width = 640;
        

    std::cout << "initializing glfw.\n";
    if(!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(width, height, "Custom Rendering Engine", nullptr, nullptr);
    if(!window) {
        glfwTerminate();
        return false;
    }
    #if defined(USE_METAL)
        std::cout << "initializing metal.\n";
        if(!initializeMetal(window)) {
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }
    #elif defined(USE_VULKAN)
        std::cout << "initializing vulkan.\n";
    #endif


    glfwSetKeyCallback(window, key_callback);

    scene = Scene();

    return true;
}

int main() {

    std::cout << "Rendering Engine started.\n";

    if(!initialize()) {
        return 1;
    }


    //rendering loop
    while (!glfwWindowShouldClose(window)) {


        
        glfwPollEvents();
        #if defined(USE_METAL)
            renderMetalFrame(window, scene);
        #elif defined(USE_VULKAN)
            renderVulkanFrame(window, scene);
        #endif
    }



    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}