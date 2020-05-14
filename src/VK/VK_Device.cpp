//
// Created by user on 4/26/20.
//

#include "VK_Device.h"
#include "Log.h"
#include "vector"
#include "set"

VK_Device::VK_Device( VK_PhysicalDevice& physical_device) {
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
VK_Device::~VK_Device()
{
    vkDestroyDevice(handle, nullptr);
    Log::status("Destroyed device");
}

VkDevice &VK_Device::getHandle() {
    return handle;
}

VK_PhysicalDevice &VK_Device::getPhysicalDevice() {
    return *physical_device;
}


