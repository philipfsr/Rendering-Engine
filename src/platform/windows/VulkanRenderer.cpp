#include <vulkan/vulkan.h>
#include <iostream>

#include "platform/windows/VulkanRenderer.h"

static VkInstance instance;
static VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

namespace {
    bool createInstance() {

        VkApplicationInfo appInfo{};
        VkInstanceCreateInfo createInfo{};

        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        if(glfwExtensions == nullptr) {
            return false;
        }

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        return vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS;
    }

    bool pickPhysicalDevice() { //picking first device found instead of "best"
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if(deviceCount == 0) {
            std::cout << "no GPUs found with Vulkan support";
            return false;
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for(const auto& device: devices) {

            if(isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if(physicalDevice == VK_NULL_HANDLE) {
            std::cout << "no GPUs found with Vulkan support";
            return false;
        }

        return true;
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {

        VkPhysicalDeviceFeatures deviceFeatures;
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
               deviceFeatures.geometryShader;
    }
}

bool initializeVulkan() {
    if(!createInstance()) {
        return false;
    }

    pickPhysicalDevice();

    return true;
}

void renderVulkanFrame(GLFWwindow* window, Scene scene) {


    // For now: drawing solid color with GPU


}

void cleanupVulkan() {
    vkDestroyInstance(instance, nullptr);
}