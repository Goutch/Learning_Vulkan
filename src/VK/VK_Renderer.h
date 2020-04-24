#pragma once


#include <GLFW/glfw3.h>
#include "VK_Instance.h"

class VK_Renderer {
    static GLFWwindow* window;
    static VK_Instance* instance;
public:
    static void draw();
    static void render();
    static void swapBuffers();
    static void init();
    static void terminate();
    static GLFWwindow* createWindow(unsigned int width,unsigned int height,const char* title);
};

