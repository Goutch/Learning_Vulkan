#pragma once

#include <vulkan/vulkan.h>

class VK_Device;
class VK_CommandPool {
    VkCommandPool command_pool;
    VK_CommandPool(VK_Device& device);
};
