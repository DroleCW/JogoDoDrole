#include "graphics/window.h"
#include "managers/inputManager.h"
#include <iostream>

Window::Window(){
    windowHandle = nullptr;
    
}

Window::Window(unsigned int screenWidth, unsigned int screenHeight, const char* name){
    windowHandle = nullptr;
    createWindow(screenWidth, screenHeight, name);

}

void Window::createWindow(unsigned int screenWidth, unsigned int screenHeight, const char* name){

    width = screenWidth;
    height = screenHeight;

    if(windowHandle)
        glfwTerminate();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    windowHandle = nullptr;
    windowHandle = glfwCreateWindow(width, height, name, NULL, NULL);
    if (windowHandle == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        return;
    }
    glfwMakeContextCurrent(windowHandle);
    //glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);
    glfwSetKeyCallback(windowHandle, InputManager::key_callback);

    initOpenGL();
}

Window::~Window(){
    glfwTerminate();
}

void Window::initOpenGL(){

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Window::refresh(){
    glfwSwapBuffers(windowHandle);
    InputManager::pollEvents(windowHandle);
}

bool Window::getShouldClose(){
    return (bool)glfwWindowShouldClose(windowHandle);
}

void Window::setShouldClose(){
    glfwSetWindowShouldClose(windowHandle, 1);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    printf("size callback\n");
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}