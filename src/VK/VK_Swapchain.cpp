//
// Created by user on 4/26/20.
//

#include "VK_Swapchain.h"
#include "Log.h"

#include <cstdint>

VK_Swapchain::VK_Swapchain(uint32_t width,
                           uint32_t height,
                           const VkInstance &instance_handle,
                           VkSurfaceKHR &surface_handle,
                           VK_PhysicalDevice& physical_device,
                           VK_Device& device) {
    this->width = width;
    this->height = height;
    this->instance_handle = &instance_handle;
    this->surface_handle = &surface_handle;
    this->physical_device = &physical_device;
    this->device=&device;
    SwapchainSupportDetails details = physical_device.getSwapchainSupportDetails();
    image_count=details.capabilities.minImageCount+1;
    if(details.capabilities.maxImageCount>0&&image_count>details.capabilities.maxImageCount)
        image_count=details.capabilities.maxImageCount;
    VkSurfaceFormatKHR surfaceFormat=chooseSwapSurfaceFormat(details.formats);
    VkPresentModeKHR present_mode=chooseSwapPresentMode(details.present_modes);
    extent=chooseSwapExtent(details.capabilities);
    format=surfaceFormat.format;
    VkSwapchainCreateInfoKHR create_info{};
    create_info.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface=surface_handle;
    create_info.imageExtent=extent;
    create_info.minImageCount=image_count;
    create_info.imageFormat=format;
    create_info.imageColorSpace=surfaceFormat.colorSpace;
    create_info.imageArrayLayers=1;
    create_info.imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;


    QueueFamilyIndices indices =physical_device.getQueueFamilyIndices();

    uint32_t queue_family_indices[]={
            indices.graphics_family.value(),
            indices.present_family.value()
    };
    if(indices.graphics_family!=indices.present_family)
    {
        create_info.imageSharingMode=VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount=2;
        create_info.pQueueFamilyIndices=queue_family_indices;
    }else{
        create_info.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
        create_info.queueFamilyIndexCount=0;
        create_info.pQueueFamilyIndices= nullptr;
    }
    create_info.preTransform=details.capabilities.currentTransform;
    create_info.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode=present_mode;
    create_info.clipped=VK_TRUE;
    //todo set to oldSwapchain when resize;
    create_info.oldSwapchain=VK_NULL_HANDLE;

    if(vkCreateSwapchainKHR(device.getHandle(),&create_info, nullptr,&handle)!=VK_SUCCESS)
    {
        Log::error("Failed to create swap chain!");
    }
    vkGetSwapchainImagesKHR(device.getHandle(), handle, &image_count, swapchain_images.data());
    swapchain_images.resize(image_count);
    vkGetSwapchainImagesKHR(device.getHandle(), handle, &image_count, nullptr);


    Log::status(std::string("Created swapchain with extent:")+std::to_string(extent.width)+"x"+std::to_string(extent.height));


}

VK_Swapchain::~VK_Swapchain() {
    for (auto imageView : swapchain_image_views) {
        vkDestroyImageView(device->getHandle(), imageView, nullptr);
    }
    vkDestroySwapchainKHR(device->getHandle(), handle, nullptr);
}

VkSurfaceFormatKHR VK_Swapchain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &available_formats) {
    for (const auto &available_format:available_formats) {
        if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB &&
            available_format.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
            return available_format;
        }
    }
    return available_formats[0];
}

VkPresentModeKHR VK_Swapchain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &available_present_modes) {
    for (const auto &available_present_mode:available_present_modes) {
        if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
            return available_present_mode;
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VK_Swapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent ={width,height};
        actualExtent.width=std::max(capabilities.maxImageExtent.width,std::min(capabilities.maxImageExtent.width,actualExtent.width));
        actualExtent.height=std::max(capabilities.maxImageExtent.height,std::min(capabilities.maxImageExtent.height,actualExtent.height));
        return actualExtent;
    }
}

void VK_Swapchain::createImageViews() {
    swapchain_image_views.resize(swapchain_images.size());
    for (int i = 0; i <swapchain_image_views.size() ; ++i) {
        VkImageViewCreateInfo create_info{};
        create_info.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        create_info.image=swapchain_images[i];
        create_info.viewType=VK_IMAGE_VIEW_TYPE_2D;
        create_info.format=format;
        create_info.components.r=VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.g=VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.b=VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.a=VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
        create_info.subresourceRange.baseMipLevel=0;
        create_info.subresourceRange.levelCount=1;
        create_info.subresourceRange.baseArrayLayer=0;
        create_info.subresourceRange.layerCount=1;
        if(vkCreateImageView(device->getHandle(),&create_info, nullptr,&swapchain_image_views[i])!=VK_SUCCESS)
        {
            Log::error("Failed to create image views");
        }
    }
}











