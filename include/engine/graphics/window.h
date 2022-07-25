#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"


#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 2


class Window{

    private:
        static GLFWwindow* windowHandle;
        static unsigned int windowWidth, windowHeight;
        static unsigned int displayWidth, displayHeight;

        Window();
        ~Window();

    public:
        

        static void createWindow(unsigned int screenWidth, unsigned int screenHeight, const char* name);
        static void refresh();
        static bool getShouldClose();
        static void setShouldClose();

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        
        static void initOpenGL();

        inline static GLFWwindow* getWindowHandle(){return windowHandle;}

        inline static unsigned int getWindowWidth(){return windowWidth;}
        inline static unsigned int getWindowHeight(){return windowHeight;}
        inline static unsigned int getDisplayWidth(){return displayWidth;}
        inline static unsigned int getDisplayHeight(){return displayHeight;}
};

