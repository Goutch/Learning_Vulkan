#pragma once

#include "VK_Shader.h"

class VK_GraphicPipeline {
    VkPipeline handle;
    VK_GraphicPipeline(VkDevice& device_handle, std::string& vert_shader_path, std::string& frag_shader);
};


