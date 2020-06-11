//
// Created by user on 4/26/20.
//

#include "VK_Device.h"
#include "VK_Swapchain.h"
#include "VK_RenderPass.h"
#include "VK_CommandPool.h"
#include "VK_GraphicPipeline.h"

#include "Log.h"
#include "vector"
#include "set"


VK_Device::VK_Device(VK_PhysicalDevice &physical_device, VkSurfaceKHR &surface_handle) {
    this->surface_handle=&surface_handle;
    this->physical_device=&physical_device;
    QueueFamilyIndices indices=physical_device.getQueueFamilyIndices();

    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    std::set<uint32_t> uniqueQueueFamilies={indices.graphics_family.value(),
                                            indices.present_family.value()};

    float priority=1.0f;//between 0 and 1.
    for (uint32_t queue_family:uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queue_create_info{};
        queue_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex=queue_family;
        queue_create_info.queueCount=1;
        queue_create_info.pQueuePriorities=&priority;
        queue_create_infos.push_back(queue_create_info);
    }

    VkDeviceCreateInfo device_create_info{};
    device_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount= static_cast<uint32_t>(queue_create_infos.size());
    device_create_info.pQueueCreateInfos=queue_create_infos.data();
    VkPhysicalDeviceFeatures device_features{};
    device_create_info.pEnabledFeatures=&device_features;
    auto& enabled_extensions=physical_device.getRequiredExtensions();
    device_create_info.enabledExtensionCount = enabled_extensions.size();
    device_create_info.ppEnabledExtensionNames=enabled_extensions.data();

    if(vkCreateDevice(physical_device.getHandle(),&device_create_info, nullptr,&handle)!=VK_SUCCESS)
    {
        Log::error("Failed to create logical device");
    }
    vkGetDeviceQueue(handle,indices.graphics_family.value(),0,&graphics_queue);
    vkGetDeviceQueue(handle,indices.present_family.value(),0,&present_queue);

}
void VK_Device::createSwapchain(int width, int height) {
    swapchain = new VK_Swapchain(static_cast<uint32_t >(width),
                                 static_cast<uint32_t >(height),
                                 *surface_handle,
                                 *this);
}
void VK_Device::createRenderPass() {
    renderPass = new VK_RenderPass(*this);
}

void VK_Device::createGraphicPipeline() {
    pipeline = new VK_GraphicPipeline("../res/shader/shader_vert.spv",
                                      "../res/shader/shader_frag.spv",
                                      *this);
}
void VK_Device::createCommandPool() {
    command_pool=new VK_CommandPool(*this);
}

void VK_Device::createFramebuffers() {
    swapchain->createFramebuffers(*renderPass);
}
VK_Device::~VK_Device()
{
    delete command_pool;
    delete pipeline;
    delete renderPass;
    delete swapchain;
    vkDestroyDevice(handle, nullptr);
    Log::status("Destroyed device");
}

VkDevice &VK_Device::getHandle() {
    return handle;
}

VK_PhysicalDevice &VK_Device::getPhysicalDevice() {
    return *physical_device;
}

VK_RenderPass &VK_Device::getRenderPass() {
    return *renderPass;
}

VK_Swapchain &VK_Device::getSwapchain() {
    return *swapchain;
}

VK_GraphicPipeline &VK_Device::getGraphicPipeline() {
    return *pipeline;
}









