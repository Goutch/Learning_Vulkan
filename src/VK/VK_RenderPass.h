#pragma once
class VK_Swapchain;
class VK_Device;
#include "vulkan/vulkan.h"
class VK_RenderPass {
    VkRenderPass handle;
    VK_Device* device= nullptr;
public:
    VK_RenderPass(VK_Device& device);
    ~VK_RenderPass();
    VkRenderPass getHandle();
};


