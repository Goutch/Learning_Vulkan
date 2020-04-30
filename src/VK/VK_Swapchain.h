

#include "vulkan/vulkan.h"
#include <GLFW/glfw3.h>
#include "vector"
#include "VK_PhysicalDevice.h"
#include "VK_Device.h"
class VK_Swapchain {
    VkSwapchainKHR handle;
    const VkInstance* instance_handle= nullptr;
    VkSurfaceKHR* surface_handle= nullptr;
    VK_PhysicalDevice* physical_device= nullptr;
    VK_Device* device= nullptr;
    uint32_t image_count;
    uint32_t width;
    uint32_t height;
    std::vector<VkImage> swapchain_images;
    std::vector<VkImageView> swapchain_image_views;
    VkExtent2D extent;
    VkFormat format;
public:
    VK_Swapchain(uint32_t width,
            uint32_t height,
            const VkInstance &instance_handle,
            VkSurfaceKHR& surface_handle,
            VK_PhysicalDevice& physical_device,
            VK_Device& device);
    ~VK_Swapchain();
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_formats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& available_present_modes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createImageViews();

};
