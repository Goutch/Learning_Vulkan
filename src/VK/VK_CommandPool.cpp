//
// Created by User on 2020-05-13.
//

#include "VK_CommandPool.h"
#include "VK_Device.h"
#include "VK_Swapchain.h"
#include "Log.h"
#include "VK_GraphicPipeline.h"
VK_CommandPool::VK_CommandPool(VK_Device &device) {
    this->device=&device;
    QueueFamilyIndices queue_family_indices=device.getPhysicalDevice().getQueueFamilyIndices();

    VkCommandPoolCreateInfo command_pool_info{};
    command_pool_info.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_info.queueFamilyIndex=queue_family_indices.graphics_family.value();
    command_pool_info.flags=0;
    if(vkCreateCommandPool(device.getHandle(),&command_pool_info, nullptr,&handle)!=VK_SUCCESS){
        Log::error("Failed to create command pool!");
    }

    command_buffers.resize(device.getSwapchain().getFrameBuffers().size());
    VkCommandBufferAllocateInfo alloc_info{};
    alloc_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.commandPool=handle;
    alloc_info.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandBufferCount=(uint32_t)command_buffers.size();

    if(vkAllocateCommandBuffers(device.getHandle(),&alloc_info,command_buffers.data())!=VK_SUCCESS){
        Log::error("Failed to allocate command buffers!");
    }

    for (size_t i = 0; i <command_buffers.size() ; ++i) {
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags=0;
        begin_info.pInheritanceInfo= nullptr;

        if(vkBeginCommandBuffer(command_buffers[i],&begin_info)!=VK_SUCCESS)
        {
            Log::error("Failed to begin recording command buffer!");
        }
        VkRenderPassBeginInfo render_pass_begin_info{};
        render_pass_begin_info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_begin_info.renderPass=device.getRenderPass().getHandle();
        render_pass_begin_info.framebuffer= device.getSwapchain().getFrameBuffers()[i];
        render_pass_begin_info.renderArea.offset={0,0};
        render_pass_begin_info.renderArea.extent=device.getSwapchain().getExtent();
        VkClearValue clear_color={0.0f,0.0f,0.0f,1.0f};
        render_pass_begin_info.clearValueCount=1;
        render_pass_begin_info.pClearValues=&clear_color;
        vkCmdBeginRenderPass(command_buffers[i],&render_pass_begin_info,VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(command_buffers[i],VK_PIPELINE_BIND_POINT_GRAPHICS,device.getGraphicPipeline().getHandle());
        vkCmdDraw(command_buffers[i],3,1,0,0);
        vkCmdEndRenderPass(command_buffers[i]);
        if(vkEndCommandBuffer(command_buffers[i])!=VK_SUCCESS){
            Log::error("Failed to record command buffer!");
        }
    }
    Log::status("Created command pool");


}

VK_CommandPool::~VK_CommandPool() {
    vkDestroyCommandPool(device->getHandle(),handle, nullptr);
    Log::status("Destroyed command pool");
}
