#include "VK/VK_Renderer.h"
GLFWwindow* window;
void init(){
    window=VK_Renderer::createWindow(900,600,"VULKAN");
    VK_Renderer::init();
}

void loop(){
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window,true);
        }
        VK_Renderer::swapBuffers();
    }
}

void cleanup(){
    VK_Renderer::terminate();
}
int main() {

    init();
    loop();
    cleanup();

    return 0;
}
