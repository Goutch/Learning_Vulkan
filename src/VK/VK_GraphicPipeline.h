#pragma once

#include "VK_Shader.h"
class VK_Swapchain;
class VK_RenderPass;
class VK_Device;
class VK_GraphicPipeline {
    VkPipeline handle;
    VkPipelineLayout layout_handle;
    VK_Device* device;

public:
    VK_GraphicPipeline(std::string vert_shader_path,
                       std::string frag_shader_path,
                       VK_Device& device);
    VkPipeline& getHandle();
    ~VK_GraphicPipeline();
};


