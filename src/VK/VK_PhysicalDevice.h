#pragma once
#include "vulkan/vulkan.h"
struct QueueFamilyIndices{
    bool has_graphics_family=false;
    uint32_t graphics_family;
    bool isComplete(){
        return has_graphics_family;
    }
};
class VK_PhysicalDevice {
    const VkInstance* vk_instance_handle;
    VkPhysicalDevice handle=VK_NULL_HANDLE;
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    QueueFamilyIndices queue_family_indices{};
public:
    VK_PhysicalDevice( const VkInstance &vk_instance_handle);
    const QueueFamilyIndices& getQueueFamilyIndices() const;
    const VkPhysicalDevice& getHandle()const;
private:
    void pickBestPhysicalDevice();
    static QueueFamilyIndices getSupportedQueueFamilies(const VkPhysicalDevice& physical_device);
    static bool isDeviceSuitable(const VkPhysicalDevice& physical_device);
    static int getScore(const VkPhysicalDevice& physical_device);

};
