#include "graphics/window.h"
#include "input/inputManager.h"
#include <iostream>

GLFWwindow* Window::windowHandle = nullptr;
unsigned int Window::windowWidth, Window::windowHeight;
unsigned int Window:: displayWidth, Window::displayHeight;


void Window::createWindow(unsigned int screenWidth, unsigned int screenHeight, const char* name){

    windowWidth = screenWidth;
    windowHeight = screenHeight;

    displayWidth = screenWidth;
    displayHeight = screenHeight;

    if(windowHandle)
        glfwTerminate();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_REFRESH_RATE, 60);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    windowHandle = nullptr;
    windowHandle = glfwCreateWindow(windowWidth, windowHeight, name, nullptr, nullptr);
    if (windowHandle == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        return;
    }
    glfwMakeContextCurrent(windowHandle);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);
    glfwSetKeyCallback(windowHandle, InputManager::key_callback);
    glfwSetMouseButtonCallback(windowHandle, InputManager::mouse_button_callback);

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

    glEnable(GL_BLEND);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_DEPTH_TEST);
}

void Window::refresh(){
    glfwSwapBuffers(windowHandle);
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
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}