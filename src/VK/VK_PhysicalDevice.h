#pragma once

#include "vulkan/vulkan.h"
#include "optional"
#include "vector"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool isComplete() {
        return graphics_family.has_value() && present_family.has_value();
    }
};
struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};
class VK_PhysicalDevice {
    const std::vector<const char*> device_required_extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

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
    const std::vector<const char *>& getRequiredExtensions() const;
    SwapchainSupportDetails getSwapchainSupportDetails();
private:
    void pickBestPhysicalDevice();
    bool checkExtensionsSupport(const VkPhysicalDevice &physical_device);
    QueueFamilyIndices getSupportedQueueFamilies(const VkPhysicalDevice &physical_device);
    SwapchainSupportDetails querySwapchainSupportDetails(const VkPhysicalDevice &physical_device);
    bool isDeviceSuitable(const VkPhysicalDevice &physical_device);

    int getScore(const VkPhysicalDevice &physical_device);

};
