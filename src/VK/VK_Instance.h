#pragma once

#include "vulkan/vulkan.h"
#include "VK_ValidationLayers.h"
#include "VK_PhysicalDevice.h"
#include "VK_Device.h"

class VK_Instance {
    VkInstance handle;
    const bool enable_validation_layers = true;
    VK_ValidationLayers* validation_layers= nullptr;
    VK_PhysicalDevice* physical_device= nullptr;
    VK_Device* device=nullptr;
public:
    VK_Instance(const char *app_name);
    ~VK_Instance();

    void getRequiredExtensions( std::vector<const char*>& extensions);
    bool checkExtensionsSupport(std::vector<const char*>& required_entension_names);

};
