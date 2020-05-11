//
// Created by user on 4/30/20.
//

#include "VK_GraphicPipeline.h"
#include "Log.h"
#include "VK_Swapchain.h"
VK_GraphicPipeline::VK_GraphicPipeline(std::string vert_shader_path,
        std::string frag_shader_path,
        VkDevice& device_handle,
        VK_Swapchain& swapchain) {
    this->device_handle=&device_handle;

    VK_Shader vert_shader(device_handle, vert_shader_path);
    VK_Shader frag_shader(device_handle, frag_shader_path);
    VkPipelineShaderStageCreateInfo vert_shader_stage_create_info;
    vert_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vert_shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vert_shader_stage_create_info.module = vert_shader.getHandle();
    vert_shader_stage_create_info.pName = "main";

    VkPipelineShaderStageCreateInfo frag_shader_stage_create_info;
    frag_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    frag_shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    frag_shader_stage_create_info.module = frag_shader.getHandle();
    frag_shader_stage_create_info.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vert_shader_stage_create_info, frag_shader_stage_create_info};

    VkPipelineVertexInputStateCreateInfo vertex_input_create_info;
    vertex_input_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input_create_info.vertexAttributeDescriptionCount = 0;
    vertex_input_create_info.pVertexBindingDescriptions = nullptr;
    vertex_input_create_info.vertexAttributeDescriptionCount = 0;
    vertex_input_create_info.pVertexAttributeDescriptions = nullptr;

    VkPipelineInputAssemblyStateCreateInfo assembly_state_create_info{};
    assembly_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    assembly_state_create_info.primitiveRestartEnable = VK_FALSE;


    VkExtent2D swapchain_extent=swapchain.getExtent();
    VkViewport viewport{};
    viewport.x = 0;
    viewport.y = 0;
    viewport.width =swapchain_extent.width;
    viewport.height=swapchain_extent.height;
    viewport.minDepth=0.0f;
    viewport.maxDepth=1.0f;

    VkRect2D scissor{};
    scissor.offset={0,0};
    scissor.extent=swapchain_extent;


    VkPipelineViewportStateCreateInfo viewport_state_create_info{};
    viewport_state_create_info.sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state_create_info.viewportCount=1;
    viewport_state_create_info.pViewports=&viewport;
    viewport_state_create_info.scissorCount=1;
    viewport_state_create_info.pScissors=&scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable=VK_FALSE;
    rasterizer.rasterizerDiscardEnable=VK_FALSE;
    rasterizer.polygonMode=VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth=1.0f;
    rasterizer.cullMode=VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace=VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable=VK_FALSE;
    rasterizer.depthBiasConstantFactor=0.0f;
    rasterizer.depthBiasClamp=0.0f;
    rasterizer.depthBiasSlopeFactor=0.0f;

    //disabled
    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable=VK_FALSE;
    multisampling.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading=1.0f;
    multisampling.pSampleMask= nullptr;
    multisampling.alphaToCoverageEnable=VK_FALSE;
    multisampling.alphaToOneEnable=VK_FALSE;

    VkPipelineColorBlendAttachmentState  color_blend_attachment{};
    color_blend_attachment.colorWriteMask=
            VK_COLOR_COMPONENT_R_BIT|
            VK_COLOR_COMPONENT_G_BIT|
            VK_COLOR_COMPONENT_B_BIT|
            VK_COLOR_COMPONENT_A_BIT;
    color_blend_attachment.blendEnable=VK_FALSE;
    color_blend_attachment.srcColorBlendFactor=VK_BLEND_FACTOR_ONE;
    color_blend_attachment.dstAlphaBlendFactor=VK_BLEND_FACTOR_ZERO;
    color_blend_attachment.colorBlendOp=VK_BLEND_OP_ADD;
    color_blend_attachment.srcAlphaBlendFactor=VK_BLEND_FACTOR_ONE;
    color_blend_attachment.dstAlphaBlendFactor=VK_BLEND_FACTOR_ZERO;
    color_blend_attachment.alphaBlendOp=VK_BLEND_OP_ADD;

    VkDynamicState dynamicStates[]={VK_DYNAMIC_STATE_VIEWPORT};

    VkPipelineDynamicStateCreateInfo dynamic_state{};
    dynamic_state.sType=VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic_state.dynamicStateCount=1;
    dynamic_state.pDynamicStates=dynamicStates;

    VkPipelineLayoutCreateInfo  pipeline_layout_create_info{};
    pipeline_layout_create_info.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_create_info.setLayoutCount=0;
    pipeline_layout_create_info.pSetLayouts= nullptr;
    pipeline_layout_create_info.pushConstantRangeCount=0;
    pipeline_layout_create_info.pPushConstantRanges= nullptr;

    if(vkCreatePipelineLayout(device_handle,&pipeline_layout_create_info, nullptr,&layout_handle)!=VK_SUCCESS)
    {
        Log::error("Failed to ccreate pipeline layout");
    }
    Log::status("Created graphic pipeline");
}

VK_GraphicPipeline::~VK_GraphicPipeline() {
    vkDestroyPipelineLayout(*device_handle,layout_handle, nullptr);
    Log::status("Destroyed graphic pipeline");
}

