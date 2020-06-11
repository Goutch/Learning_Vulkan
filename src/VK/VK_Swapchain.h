

#include "vulkan/vulkan.h"
#include <GLFW/glfw3.h>
#include "vector"
#include "VK_PhysicalDevice.h"
#include "VK_Device.h"
#include "VK_RenderPass.h"

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
    std::vector<VkFramebuffer> frame_buffers;
    VkExtent2D extent;
    VkFormat format;
public:
    VK_Swapchain(uint32_t width,
            uint32_t height,
            VkSurfaceKHR& surface_handle,
            VK_Device& device);
    ~VK_Swapchain();
    void createFramebuffers(VK_RenderPass& render_pass);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_formats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& available_present_modes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createImageViews();
    VkSwapchainKHR& getHandle();
    VkExtent2D getExtent();
    VkFormat getFormat();
    std::vector<VkFramebuffer>& getFrameBuffers();

};
