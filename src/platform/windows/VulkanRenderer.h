#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "scene/Scene.h"

bool initializeVulkan();

void renderVulkanFrame(GLFWwindow* window, Scene scene);

void cleanupVulkan();