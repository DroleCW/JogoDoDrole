#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "graphics/shaderProgram.h"
#include "graphics/textureManager.h"
#include "math/vec2f.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[16] = {
         0.0f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.0f, 250.0f,
         0.5f, 0.0f, 200.0f, 250.0f,
         0.5f, 0.5f, 200.0f, 0.0f
    };
    unsigned int indices[6] = {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int vbo;

    unsigned int ebo;

    unsigned int vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


    vec2f first(2, 3);
    vec2f second(4, 5);
    vec2f third = first+second;
    printf("%f, %f, %f\n", first.x, second.x, third.x);
    printf("%f, %f, %f\n", first.y, second.y, third.y);
    printf("%f\n", third.length());
    third = 3*third;
    printf("%f\n", third.length());



    TextureManager testTextureManager;

    ShaderProgram testShaderProgram;
    testShaderProgram.addShaderFromFile("shaders/simpleTestVertexShader.sdv");
    testShaderProgram.addShaderFromFile("shaders/simpleTestFragmentShader.sdf");
    testShaderProgram.link();

    testShaderProgram.bind();

    testShaderProgram.setUniform("textureSlot", 0);

    float translationX = 0.0f;
    float translationY = 0.0f;

    testTextureManager.loadTexture(TEST_TEXTURE2_LOCATION);
    testTextureManager.bindTexture(TEST_TEXTURE2_LOCATION, 0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)){
        // input
        // -----
        processInput(window);

        translationX += 0.01f;
        translationY += 0.01f;

        if(translationX > 1.2f){
            translationX = 0.0f;
            translationY = 0.0f;
        }

        testShaderProgram.setUniform("translation", translationX, translationY);

        // render
        // ------
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}