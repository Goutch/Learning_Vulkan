#pragma once

#include "vulkan/vulkan.h"
#include "VK_ValidationLayers.h"

class VK_Instance {
    VkInstance instance_handle;

    const bool enable_validation_layers = true;
    VK_ValidationLayers* validation_layers= nullptr;
public:
    VK_Instance(const char *app_name);

    ~VK_Instance();

    bool checkExtensionsSupport(const char **extensions_name, uint32_t count);
};
