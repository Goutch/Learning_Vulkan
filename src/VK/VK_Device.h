#pragma once

#include <vulkan/vulkan.h>
#include "VK_PhysicalDevice.h"

class VK_Device {
    VkDevice handle;
    VkQueue graphicsQueue;
public:
    VK_Device(const VK_PhysicalDevice& physical_device);
    ~VK_Device();
};

