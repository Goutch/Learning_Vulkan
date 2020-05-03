//
// Created by user on 4/30/20.
//

#include "VK_GraphicPipeline.h"

VK_GraphicPipeline::VK_GraphicPipeline(VkDevice &device_handle, std::string &vert_shader_path, std::string &frag_shader_path) {
    VK_Shader vert_shader(device_handle,vert_shader_path);
    VK_Shader frag_shader(device_handle,frag_shader_path);
    VkPipelineShaderStageCreateInfo vert_shader_stage_create_info;
    vert_shader_stage_create_info.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vert_shader_stage_create_info.stage=VK_SHADER_STAGE_VERTEX_BIT;
    vert_shader_stage_create_info.module=vert_shader.getHandle();
    vert_shader_stage_create_info.pName="main";
    VkPipelineShaderStageCreateInfo frag_shader_stage_create_info;
    frag_shader_stage_create_info.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    frag_shader_stage_create_info.stage=VK_SHADER_STAGE_FRAGMENT_BIT;
    frag_shader_stage_create_info.module=frag_shader.getHandle();
    frag_shader_stage_create_info.pName="main";

    VkPipelineShaderStageCreateInfo shaderStages[]={vert_shader_stage_create_info,frag_shader_stage_create_info};
}



