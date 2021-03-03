#pragma once

#include "vulkan/vulkan.h"
#include "VK_ValidationLayers.h"
#include "VK_PhysicalDevice.h"
#include "VK_Device.h"
#include "VK_Swapchain.h"
#include "VK_GraphicPipeline.h"
#include "VK_RenderPass.h"

class VK_Instance {
    const bool ENABLE_VALIDATION_LAYERS = true;

    VkInstance handle;
    VkSurfaceKHR surface_handle;
    GLFWwindow* window_handle= nullptr;
    VK_ValidationLayers* validation_layers= nullptr;
    VK_PhysicalDevice* physical_device= nullptr;
    VK_Device* device=nullptr;

public:
    VK_Instance(GLFWwindow* window);
    ~VK_Instance();

private:
    void createInstance();
    void createSurface();
    void getRequiredExtensions( std::vector<const char*>& extensions);
    bool checkExtensionsSupport(std::vector<const char*>& required_extension_names);

};
