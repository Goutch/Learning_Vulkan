
#include "VK_Renderer.h"
#include "Log.h"

GLFWwindow* VK_Renderer::window=nullptr;
VK_Instance* VK_Renderer::instance= nullptr;

GLFWwindow *VK_Renderer::createWindow(unsigned int width, unsigned int height, const char *title) {
    if (!glfwInit())
    {
        Log::error("glfwInit() failed.");
    }
    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE,GLFW_FALSE);
    window = glfwCreateWindow(width,height,title,nullptr,nullptr);
    return window;
}

void VK_Renderer::init() {
    if(!window||!glfwInit())Log::error("Create window before initializing renderer");

    if(!glfwVulkanSupported())
    {
        Log::error("Vulkan is not supported");
    }
    instance=new VK_Instance(window);
    glfwShowWindow(window);
    Log::status("Window opened");

}




void VK_Renderer::render() {

}

void VK_Renderer::draw() {

}

void VK_Renderer::swapBuffers() {

}

void VK_Renderer::terminate() {
    if(instance)delete instance;
    if(window)glfwDestroyWindow(window);
    glfwTerminate();
}
