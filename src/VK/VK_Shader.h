#pragma once

#include "vector"
#include "vulkan/vulkan.h"
#include "string"
class VK_Shader {
    VkShaderModule handle;
    VkDevice* device_handle;

    static std::vector<char> readFile(const std::string& filename);

public:
    VK_Shader(VkDevice& device_handle,const std::string& file);

    ~VK_Shader();

    VkShaderModule& getHandle();
};


