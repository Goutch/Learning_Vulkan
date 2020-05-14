#pragma once

#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"
#include "VK_PhysicalDevice.h"

class VK_Device {
    VkDevice handle;

    VkQueue graphics_queue;
    VkQueue present_queue;
    VK_PhysicalDevice* physical_device;
public:
    VK_Device(VK_PhysicalDevice& physical_device);
    VkDevice& getHandle();
    VK_PhysicalDevice& getPhysicalDevice();
    ~VK_Device();
};

