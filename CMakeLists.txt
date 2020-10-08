cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(App)

message("Vulkan...")
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

message("GLFW...")
include_directories("dependencies/glfw/include")
add_subdirectory("dependencies/glfw")

message("GLM...")
include_directories("dependencies/glm")
add_subdirectory("dependencies/glm")

include_directories("src")

add_executable (${PROJECT_NAME}
        src/main.cpp
        src/Log.cpp
        src/Log.h
        src/VK/VK_Renderer.cpp
        src/VK/VK_Renderer.h
        src/VK/VK_Instance.cpp
        src/VK/VK_Instance.h
        src/VK/VK_ValidationLayers.cpp
        src/VK/VK_ValidationLayers.h
        src/VK/VK_PhysicalDevice.cpp
        src/VK/VK_PhysicalDevice.h
        src/VK/VK_Device.cpp
        src/VK/VK_Device.h
        src/VK/VK_Swapchain.cpp
        src/VK/VK_Swapchain.h
        src/VK/VK_Shader.cpp
        src/VK/VK_Shader.h
        src/VK/VK_GraphicPipeline.cpp
        src/VK/VK_GraphicPipeline.h
        src/VK/VK_RenderPass.cpp
        src/VK/VK_RenderPass.h
        src/VK/VK_CommandPool.cpp
        src/VK/VK_CommandPool.h)

target_link_libraries(${PROJECT_NAME} glfw ${Vulkan_LIBRARY})