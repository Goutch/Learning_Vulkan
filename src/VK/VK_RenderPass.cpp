//
// Created by User on 2020-05-09.
//

#include "VK_RenderPass.h"
#include "vulkan//vulkan.h"
#include "VK_Swapchain.h"
#include "VK_Device.h"
#include "Log.h"
VK_RenderPass::VK_RenderPass(VK_Device& device,VK_Swapchain& swapchain) {
    this->device=&device;

    VkAttachmentDescription  color_attachment{};
    color_attachment.format=swapchain.getFormat();
    color_attachment.samples=VK_SAMPLE_COUNT_1_BIT;
    color_attachment.loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    color_attachment.storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    color_attachment.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    color_attachment.finalLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference color_attachment_ref{};
    color_attachment_ref.attachment=0;//shader color output at layout position 0
    color_attachment_ref.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription  subpass{};
    subpass.pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount=1;
    subpass.pColorAttachments=&color_attachment_ref;


    VkRenderPassCreateInfo render_pass_create_info{};
    render_pass_create_info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_create_info.attachmentCount=1;
    render_pass_create_info.pAttachments=&color_attachment;
    render_pass_create_info.subpassCount=1;
    render_pass_create_info.pSubpasses=&subpass;

    if(vkCreateRenderPass(device.getHandle(),&render_pass_create_info, nullptr,&handle)){
        Log::error("Failed to create render pass!");
    }
    Log::status("Created render pass");


}

VK_RenderPass::~VK_RenderPass() {
    vkDestroyRenderPass(device->getHandle(), handle, nullptr);
    Log::status("Destroyed render pass");
}

VkRenderPass VK_RenderPass::getHandle() {
    return handle;
}
