#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 5


class Window{

    private:
        GLFWwindow* windowHandle;
        unsigned int width, height;

    public:
        Window();
        Window(unsigned int screenWidth, unsigned int screenHeight, const char* name);
        ~Window();

        void createWindow(unsigned int screenWidth, unsigned int screenHeight, const char* name);
        void refresh();
        bool getShouldClose();
        void setShouldClose();

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        
        static void initOpenGL();

};

