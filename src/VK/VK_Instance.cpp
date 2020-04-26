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

    std::vector<const char*> required_extensions;
    getRequiredExtensions(required_extensions);
    create_info.enabledExtensionCount = static_cast<uint32_t>(required_extensions.size());
    create_info.ppEnabledExtensionNames = required_extensions.data();
    create_info.enabledLayerCount = 0;

    if (checkExtensionsSupport(required_extensions)) {
        if(enable_validation_layers)
        {
            validation_layers=new VK_ValidationLayers();
            create_info.enabledLayerCount=validation_layers->getCount();
            create_info.ppEnabledLayerNames=validation_layers->getValidationLayersNames();
            create_info.pNext=&validation_layers->getCreateInfo();
        } else{
            create_info.enabledLayerCount=0;
            create_info.pNext= nullptr;
        }
        if (vkCreateInstance(&create_info, nullptr, &handle) != VK_SUCCESS) {
            Log::error("vkCreateInstance() failed.");
        }

    } else {
        Log::error("Missing extensions to create vulkan instance");
    }
    if(enable_validation_layers)
    {
        validation_layers->init(handle);
    }
    Log::status("Vulkan instance initialized");

    physical_device=new VK_PhysicalDevice(handle);
    device=new VK_Device(*physical_device);
}
void VK_Instance::getRequiredExtensions(std::vector<const char *>& extensions) {
    uint32_t glfw_extension_count = 0;
    const char **glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    for (int i = 0; i <glfw_extension_count ; ++i) {
        extensions.push_back(glfw_extensions[i]);
    }
    if(enable_validation_layers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
}
bool VK_Instance::checkExtensionsSupport(std::vector<const char *>& required_extension_names) {
    uint32_t instance_extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, nullptr);
    std::vector<VkExtensionProperties> instance_supported_extensions(instance_extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, instance_supported_extensions.data());

    Log::message("Looking for required vulkan extensions:");
    bool succes=true;
    for (auto required_extension_name:required_extension_names) {
        Log::message("\t" +std::string(required_extension_name) +"...");
        bool found=false;
        for (const auto& supported_extension:instance_supported_extensions) {
            if(strcmp(required_extension_name,supported_extension.extensionName)==0)
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
    if(device)delete device;
    if(physical_device)delete physical_device;
    if(enable_validation_layers&&validation_layers)delete validation_layers;
    vkDestroyInstance(handle, nullptr);
    Log::status("Vulkan instance terminated");
}






