//
// Created by user on 4/30/20.
//

#include "VK_Shader.h"
#include "Log.h"
#include "fstream"
VK_Shader::VK_Shader(VkDevice& device_handle,const std::string &file) {
    this->device_handle=&device_handle;
    auto code=readFile(file);
    VkShaderModuleCreateInfo create_info{};
    create_info.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize=code.size();
    create_info.pCode= reinterpret_cast<const uint32_t*>(code.data());
    if(vkCreateShaderModule(device_handle,&create_info, nullptr,&handle)!=VK_SUCCESS)
    {
        Log::error("Failed to create shader module!");
    }
}

std::vector<char> VK_Shader::readFile(const std::string &filename) {
    std::ifstream file(filename,std::ios::ate|std::ios::binary);

    if(!file.is_open())
    {
        Log::error("Failed to open file");
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

VkShaderModule &VK_Shader::getHandle() {
    return handle;
}

VK_Shader::~VK_Shader() {
    vkDestroyShaderModule(*device_handle,handle, nullptr);
}

