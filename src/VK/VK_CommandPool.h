#pragma once

#include <vulkan/vulkan.h>
#include "vector"
class VK_Swapchain;

class VK_Device;
class VK_CommandPool {


    VkCommandPool handle;
    std::vector<VkCommandBuffer> command_buffers;
    VK_Device* device;

public:
    VK_CommandPool(VK_Device &device);

    ~VK_CommandPool();
};
