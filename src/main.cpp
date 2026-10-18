#include <iostream>
#include <GLFW/glfw3.h>

GLFWwindow* window;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void initialize() {

    //GLFW----------
    std::cout << "initializing glfw./n";
    if(!glfwInit()) {
        //initionalization failed
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(640, 480, "Custom Rendering Engine", nullptr, nullptr);
    if(!window) {
        glfwTerminate();
    }

    glfwSetKeyCallback(window, key_callback);

    //-------------
}

int main() {

    std::cout << "Rendering Engine started./n";

    initialize();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}