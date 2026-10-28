#pragma once

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "scene/Scene.cpp"

void renderVulkanFrame(GLFWwindow* window, Scene scene);