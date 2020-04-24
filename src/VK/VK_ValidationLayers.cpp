//
// Created by user on 4/24/20.
//

#include "Log.h"
#include "VK_ValidationLayers.h"
#include "vulkan/vulkan.hpp"
VK_ValidationLayers::VK_ValidationLayers() {
    if(!checkForSupport())
    {
        Log::error("Some requested validation layers are not supported!");
    }
}

bool VK_ValidationLayers::checkForSupport() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
    Log::message("Looking for vulkan validation layers support:");
    bool succces=true;
    for (const char* layer_name:validation_layers) {
        Log::message("\t"+std::string(layer_name)+"...");
        bool found=false;
        for (const auto& layer_property:available_layers) {
            if(strcmp(layer_name,layer_property.layerName)==0)
            {
                found=true;
                    Log::message("\t\tFOUND!");
                break;
            }
        }
        if(!found)
        {
            succces= false;
            Log::message("\t\tMISSING!");
        }
    }
    return succces;
}

char **VK_ValidationLayers::getValidationLayersNames() {
    return nullptr;
}
