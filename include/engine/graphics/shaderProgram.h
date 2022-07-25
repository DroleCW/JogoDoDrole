#pragma once
#include <fstream>
#include <stdio.h>

class ShaderProgram{

    private:
        unsigned int id;
    
    public:
        ShaderProgram();
        ~ShaderProgram();

        const unsigned int getID() const;

        void addShaderFromFile(const char* path);
        void link();
        void bind();

        void setUniform(const char* name, int* v, int size);

        void setUniform(const char* name, int x);
        void setUniform(const char* name, int x, int y);
        void setUniform(const char* name, int x, int y, int z);

        void setUniform(const char* name, float x);
        void setUniform(const char* name, float x, float y);
        void setUniform(const char* name, float x, float y, float z);
};