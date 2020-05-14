//
// Created by User on 2020-05-13.
//

#include "VK_CommandPool.h"
#include "VK_Device.h"
VK_CommandPool::VK_CommandPool(VK_Device &device) {
    QueueFamilyIndices queue_family_indices=device.getPhysicalDevice().getQueueFamilyIndices();

    VkCommandPoolCreateInfo command_pool_info{};
    command_pool_info.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_info.queueFamilyIndex=queue_family_indices.graphics_family.value();
    command_pool_info.flags=0;
}
