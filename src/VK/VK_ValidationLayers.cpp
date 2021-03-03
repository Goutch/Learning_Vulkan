#include "Log.h"
#include "VK_ValidationLayers.h"
#include "vulkan/vulkan.hpp"

VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                            "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL VK_ValidationLayers::debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData) {
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        Log::warning("validation layer:" + std::string(pCallbackData->pMessage));
    } else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        Log::warning("validation layer:" + std::string(pCallbackData->pMessage));
    }
    return VK_FALSE;
}

VK_ValidationLayers::VK_ValidationLayers() {

    if (!checkForSupport()) {
        Log::error("Some requested validation layers are not supported!");
    }

    create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    create_info.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    create_info.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    create_info.pfnUserCallback = debugCallback;
    create_info.pUserData = nullptr;

}

void VK_ValidationLayers::init(const VkInstance &vk_instance_handle) {
    this->vk_instance_handle = &vk_instance_handle;
    if (createDebugUtilsMessengerEXT(*this->vk_instance_handle, &create_info, nullptr, &debug_messenger) !=
        VK_SUCCESS) {
        Log::error("Failed to set up debug messenger!");
    }
}

bool VK_ValidationLayers::checkForSupport() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
    Log::message("Looking for vulkan validation layers support:");
    bool succces = true;
    for (const char *layer_name:validation_layers) {
        Log::message("\t" + std::string(layer_name) + "...");
        bool found = false;
        for (const auto &layer_property:available_layers) {
            if (strcmp(layer_name, layer_property.layerName) == 0) {
                found = true;
                Log::message("\t\tFOUND!");
                break;
            }
        }
        if (!found) {
            succces = false;
            Log::message("\t\tMISSING!");
        }
    }
    return succces;
}

const char **VK_ValidationLayers::getValidationLayersNames() {
    return validation_layers.data();
}

uint32_t VK_ValidationLayers::getCount() {
    return validation_layers.size();
}

VK_ValidationLayers::~VK_ValidationLayers() {
    if (debug_messenger)destroyDebugUtilsMessengerEXT(*vk_instance_handle, debug_messenger, nullptr);
}

const VkDebugUtilsMessengerCreateInfoEXT &VK_ValidationLayers::getCreateInfo() {
    return create_info;
}








