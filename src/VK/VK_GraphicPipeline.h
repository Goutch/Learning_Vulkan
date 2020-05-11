#pragma once

#include "VK_Shader.h"
class VK_Swapchain;

class VK_GraphicPipeline {
    VkPipeline handle;
    VkPipelineLayout layout_handle;
    VkDevice* device_handle;

public:
    VK_GraphicPipeline(std::string vert_shader_path, std::string frag_shader_path,VkDevice& device_handle, VK_Swapchain& swapchain);

    ~VK_GraphicPipeline();
};


