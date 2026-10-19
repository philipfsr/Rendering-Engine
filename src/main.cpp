#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>

#include "platform/macos/MetalRenderer.h"

GLFWwindow* window;
int height, width;

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
    if(!initializeMetal(window)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    glfwSetKeyCallback(window, key_callback);

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
        renderMetalFrame(window);
    }



    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}