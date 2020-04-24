//
// Created by user on 4/24/20.
//

#include <vector>
#include "VK_Instance.h"

#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"
#include "Log.h"
#include<string.h>
VK_Instance::VK_Instance(const char *app_name) {
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = app_name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "EngineNamePlaceHodler";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    uint32_t glfw_extension_count = 0;
    const char **glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    create_info.enabledExtensionCount = glfw_extension_count;
    create_info.ppEnabledExtensionNames = glfw_extensions;
    create_info.enabledLayerCount = 0;

    if (checkExtensionsSupport(glfw_extensions, glfw_extension_count)) {
        if (vkCreateInstance(&create_info, nullptr, &instance_handle) != VK_SUCCESS) {
            Log::error("vkCreateInstance() failed.");
        }

    } else {
        Log::error("Missing extensions to create vulkan instance");
    }
    if(enable_validation_layers)
    {
        validation_layers=new VK_ValidationLayers();
    }
}

bool VK_Instance::checkExtensionsSupport(const char** extensions_name, uint32_t count) {
    uint32_t instance_extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, nullptr);
    std::vector<VkExtensionProperties> instance_extensions(instance_extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, instance_extensions.data());

    Log::message("Looking for required vulkan extensions:");
    bool succes=true;
    for (int i = 0; i < count; ++i) {
        Log::message("\t" +std::string(extensions_name[i]) +"...");
        bool found=false;
        for (const auto extension:instance_extensions) {
            if(strcmp(extensions_name[i],extension.extensionName)==0)
            {
                Log::message("\t\tFOUND!");
                found=true;
                break;
            }
        }
        if(!found)
        {
            succes=false;
            Log::message("\t\tMISSING!");
        }
    }
    return succes;
}


VK_Instance::~VK_Instance() {
    if(enable_validation_layers)delete validation_layers;
    vkDestroyInstance(instance_handle, nullptr);
}


