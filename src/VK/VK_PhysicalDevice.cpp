//
// Created by user on 4/25/20.
//

#include <vector>
#include "VK_PhysicalDevice.h"
#include "Log.h"
#include "map"
VK_PhysicalDevice::VK_PhysicalDevice(const VkInstance& vk_instance_handle) {
    this->vk_instance_handle=&vk_instance_handle;
    Log::status("Looking for suitable GPU...");
    pickBestPhysicalDevice();
}

void VK_PhysicalDevice::pickBestPhysicalDevice() {
    uint32_t device_count=0;
    vkEnumeratePhysicalDevices(*vk_instance_handle,&device_count, nullptr);
    if(device_count==0)
    {
        Log::error("No available GPU!");
    }
    std::vector<VkPhysicalDevice> available_physical_devices=std::vector<VkPhysicalDevice>(device_count);
    vkEnumeratePhysicalDevices(*vk_instance_handle, &device_count, available_physical_devices.data());

    std::multimap<int,VkPhysicalDevice> suitable_devices_map;
    for (const VkPhysicalDevice& physical_device:available_physical_devices) {
        if(isDeviceSuitable(physical_device))
        {
            int score=getScore(physical_device);
            suitable_devices_map.emplace(score, physical_device);
        }
    }
    if(!suitable_devices_map.empty())
    {
        handle= suitable_devices_map.rbegin()->second;
        vkGetPhysicalDeviceProperties(handle, &properties);
        vkGetPhysicalDeviceFeatures(handle, &features);
        queue_family_indices=getSupportedQueueFamilies(handle);
        Log::message(std::string("\tFOUND:")+properties.deviceName);
    } else{
        Log::error("\tFailed to find a suitable GPU!");
    }

}

int VK_PhysicalDevice::getScore(const VkPhysicalDevice &physical_device) {
    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;
    vkGetPhysicalDeviceProperties(physical_device, &device_properties);
    vkGetPhysicalDeviceFeatures(physical_device, &device_features);
    int score=1;
    if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }
    return score;
}
const QueueFamilyIndices &VK_PhysicalDevice::getQueueFamilyIndices() const {
    return queue_family_indices;
}
bool VK_PhysicalDevice::isDeviceSuitable(VkPhysicalDevice const &physical_device) {
    QueueFamilyIndices queue_families_indices=getSupportedQueueFamilies(physical_device);

    return queue_families_indices.isComplete();
}

QueueFamilyIndices VK_PhysicalDevice::getSupportedQueueFamilies(VkPhysicalDevice const &physical_device) {
    QueueFamilyIndices indices;
    uint32_t queue_family_count=0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device,&queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> supported_queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, supported_queue_families.data());

    for (int i=0;i<queue_family_count;++i) {
        if(supported_queue_families.at(i).queueFlags&VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphics_family=i;
            indices.has_graphics_family=true;
        }
        if(indices.isComplete())break;
    }

    return indices;
}

const VkPhysicalDevice &VK_PhysicalDevice::getHandle() const {
    return handle;
}


