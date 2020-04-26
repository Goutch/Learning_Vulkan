//
// Created by user on 4/26/20.
//

#include "VK_Device.h"
#include "Log.h"
VK_Device::VK_Device(const VK_PhysicalDevice& physical_device) {
    VkDeviceQueueCreateInfo queue_create_info{};
    QueueFamilyIndices queue_family_indices=physical_device.getQueueFamilyIndices();
    queue_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex=queue_family_indices.graphics_family;
    queue_create_info.queueCount=1;
    float priority=1.0f;//between 0 and 1.
    queue_create_info.pQueuePriorities=&priority;

    VkPhysicalDeviceFeatures device_features{};

    VkDeviceCreateInfo device_create_info{};
    device_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.pQueueCreateInfos=&queue_create_info;
    device_create_info.queueCreateInfoCount=1;
    device_create_info.pEnabledFeatures=&device_features;
    device_create_info.enabledExtensionCount = 0;

    if(vkCreateDevice(physical_device.getHandle(),&device_create_info, nullptr,&handle)!=VK_SUCCESS)
    {
        Log::error("Failed to create logical device");
    }
    vkGetDeviceQueue(handle,queue_family_indices.graphics_family,0,&graphicsQueue);
}
VK_Device::~VK_Device()
{
    vkDestroyDevice(handle, nullptr);
}