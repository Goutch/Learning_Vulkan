

#include "vulkan/vulkan.h"
#include <GLFW/glfw3.h>
class VK_Swapchain {

    const VkInstance* vk_instance_handle= nullptr;
    VkSurfaceKHR* surface_handle= nullptr;
public:
    VK_Swapchain(const VkInstance &vk_instance_handle,VkSurfaceKHR& surface_handle);

    ~VK_Swapchain();


};
