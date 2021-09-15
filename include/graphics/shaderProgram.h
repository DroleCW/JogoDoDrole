#pragma once

#include <glad/glad.h>
#include <fstream>
#include <stdio.h>

class shaderProgram{

    private:
        unsigned int id;
    
    public:
        shaderProgram();
        ~shaderProgram();

        const unsigned int getID() const;

        void addShaderFromFile(const char* path);
        void link();
        void bind();

        void setUniform(const char* name, int x);
        void setUniform(const char* name, int x, int y);
        void setUniform(const char* name, int x, int y, int z);

        void setUniform(const char* name, float x);
        void setUniform(const char* name, float x, float y);
        void setUniform(const char* name, float x, float y, float z);
};