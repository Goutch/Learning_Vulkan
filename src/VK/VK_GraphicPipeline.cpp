

#include "VK_GraphicPipeline.h"
#include "Log.h"
#include "VK_Swapchain.h"
#include "VK_Device.h"
#include "VK_RenderPass.h"

VK_GraphicPipeline::VK_GraphicPipeline(std::string vert_shader_path,
        std::string frag_shader_path,
        VK_Device& device) {
    this->device=&device;

    VK_Shader vert_shader(device.getHandle(), vert_shader_path);
    VK_Shader frag_shader(device.getHandle(), frag_shader_path);
    VkPipelineShaderStageCreateInfo vert_shader_stage_create_info{};
    vert_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vert_shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vert_shader_stage_create_info.module = vert_shader.getHandle();
    vert_shader_stage_create_info.pName = "main";

    VkPipelineShaderStageCreateInfo frag_shader_stage_create_info{};
    frag_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    frag_shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    frag_shader_stage_create_info.module = frag_shader.getHandle();
    frag_shader_stage_create_info.pName = "main";

    VkPipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_create_info, frag_shader_stage_create_info};

    VkPipelineVertexInputStateCreateInfo vertex_input_state{};
    vertex_input_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input_state.vertexAttributeDescriptionCount = 0;
    vertex_input_state.pVertexBindingDescriptions = nullptr;
    vertex_input_state.vertexAttributeDescriptionCount = 0;
    vertex_input_state.pVertexAttributeDescriptions = nullptr;

    VkPipelineInputAssemblyStateCreateInfo input_assembly_state{};
    input_assembly_state.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly_state.primitiveRestartEnable = VK_FALSE;


    VkExtent2D swapchain_extent=device.getSwapchain().getExtent();
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


    VkPipelineViewportStateCreateInfo viewport_state{};
    viewport_state.sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.viewportCount=1;
    viewport_state.pViewports=&viewport;
    viewport_state.scissorCount=1;
    viewport_state.pScissors=&scissor;

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


    VkPipelineColorBlendStateCreateInfo color_blending{};
    color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blending.logicOpEnable = VK_FALSE;
    color_blending.logicOp = VK_LOGIC_OP_COPY; // Optional
    color_blending.attachmentCount = 1;
    color_blending.pAttachments = &color_blend_attachment;
    color_blending.blendConstants[0] = 0.0f; // Optional
    color_blending.blendConstants[1] = 0.0f; // Optional
    color_blending.blendConstants[2] = 0.0f; // Optional
    color_blending.blendConstants[3] = 0.0f; // Optional



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

    if(vkCreatePipelineLayout(device.getHandle(),&pipeline_layout_create_info, nullptr,&layout_handle)!=VK_SUCCESS)
    {
        Log::error("Failed to create pipeline layout");
    }

    VkGraphicsPipelineCreateInfo graphics_pipeline_create_info{};
    graphics_pipeline_create_info.sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    graphics_pipeline_create_info.stageCount=2;
    graphics_pipeline_create_info.pStages=shader_stages;
    graphics_pipeline_create_info.pVertexInputState=&vertex_input_state;
    graphics_pipeline_create_info.pInputAssemblyState=&input_assembly_state;
    graphics_pipeline_create_info.pViewportState=&viewport_state;
    graphics_pipeline_create_info.pRasterizationState=&rasterizer;
    graphics_pipeline_create_info.pMultisampleState=&multisampling;
    graphics_pipeline_create_info.pDepthStencilState= nullptr;
    graphics_pipeline_create_info.pColorBlendState=&color_blending;
    graphics_pipeline_create_info.pDynamicState= nullptr;

    graphics_pipeline_create_info.layout=layout_handle;
    graphics_pipeline_create_info.renderPass=device.getRenderPass().getHandle();
    graphics_pipeline_create_info.subpass=0;
    graphics_pipeline_create_info.basePipelineHandle=VK_NULL_HANDLE;
    graphics_pipeline_create_info.basePipelineIndex=-1;

    if(vkCreateGraphicsPipelines(device.getHandle(),VK_NULL_HANDLE,1,&graphics_pipeline_create_info, nullptr,&handle)!=VK_SUCCESS)
    {
        Log::error("Failed to create graphics pipeline!");
    }

    Log::status("Created graphic pipeline");
}

VK_GraphicPipeline::~VK_GraphicPipeline() {
    vkDestroyPipelineLayout(device->getHandle(),layout_handle, nullptr);
    vkDestroyPipeline(device->getHandle(),handle, nullptr);
    Log::status("Destroyed graphic pipeline");
}

VkPipeline &VK_GraphicPipeline::getHandle() {
    return handle;
}



