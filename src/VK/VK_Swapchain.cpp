//
// Created by user on 4/26/20.
//

#include "VK_Swapchain.h"
#include "Log.h"
VK_Swapchain::VK_Swapchain(VkInstance const &vk_instance_handle, VkSurfaceKHR &surface_handle) {
    this->vk_instance_handle=&vk_instance_handle;
    this->surface_handle=&surface_handle;
}

VK_Swapchain::~VK_Swapchain() {

}



