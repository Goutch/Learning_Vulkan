#pragma once

#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"
#include "VK_PhysicalDevice.h"

class VK_Device {
    VkDevice handle;
    VkQueue graphics_queue;
    VkQueue present_queue;
public:
    VK_Device(const VK_PhysicalDevice& physical_device);
    ~VK_Device();
};

