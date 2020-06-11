#pragma once

#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"
#include "VK_PhysicalDevice.h"
class VK_RenderPass;
class VK_Swapchain;
class VK_GraphicPipeline;
class VK_CommandPool;
class VK_Device {
    VkDevice handle;

    VkQueue graphics_queue;
    VkQueue present_queue;
    VkSurfaceKHR* surface_handle;
    VK_PhysicalDevice* physical_device;
    VK_Swapchain* swapchain=nullptr;
    VK_RenderPass* renderPass=nullptr;
    VK_GraphicPipeline* pipeline=nullptr;
    VK_CommandPool* command_pool=nullptr;
public:
    VK_Device(VK_PhysicalDevice& physical_device, VkSurfaceKHR& surface_handle);
    void createSwapchain(int width,int height);
    void createRenderPass();
    void createGraphicPipeline();
    void createFramebuffers();
    void createCommandPool();
    VK_Swapchain& getSwapchain();
    VK_GraphicPipeline& getGraphicPipeline();
    VK_RenderPass& getRenderPass();
    VkDevice& getHandle();
    VK_PhysicalDevice& getPhysicalDevice();
    ~VK_Device();
};

