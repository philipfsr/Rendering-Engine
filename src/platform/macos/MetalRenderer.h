#pragma once

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "scene/Scene.cpp"

struct GLFWwindow;

bool initializeMetal(GLFWwindow* window);

void renderMetalFrame(GLFWwindow* window, Scene scene);