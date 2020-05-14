#include "Log.h"
#include "VK/VK_Renderer.h"
GLFWwindow* window;
void init(){
    window=VK_Renderer::createWindow(900,600,"VULKAN");
    VK_Renderer::init();
}

void loop(){
    glfwSwapInterval(60);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window,true);
        }
        glfwSwapBuffers(window);
        VK_Renderer::swapBuffers();
    }
    Log::status("Window closed");
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