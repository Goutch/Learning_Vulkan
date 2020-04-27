#pragma once

#include "vulkan/vulkan.h"
#include "optional"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool isComplete() {
        return graphics_family.has_value() && present_family.has_value();
    }
};

class VK_PhysicalDevice {
    const VkInstance *vk_instance_handle;
    VkSurfaceKHR* surface_handle;
    VkPhysicalDevice handle = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    QueueFamilyIndices queue_family_indices{};
public:
    VK_PhysicalDevice(const VkInstance &vk_instance_handle, VkSurfaceKHR &surface_handle);

    const QueueFamilyIndices &getQueueFamilyIndices() const;

    const VkPhysicalDevice &getHandle() const;
    const VkPhysicalDeviceFeatures& getFeatures() const;
    const VkPhysicalDeviceProperties& getProperties() const;
private:
    void pickBestPhysicalDevice();

    QueueFamilyIndices getSupportedQueueFamilies(const VkPhysicalDevice &physical_device);

    bool isDeviceSuitable(const VkPhysicalDevice &physical_device);

    int getScore(const VkPhysicalDevice &physical_device);

};
