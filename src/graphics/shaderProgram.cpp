#include "graphics/shaderProgram.h"
#include <glad/glad.h>

ShaderProgram::ShaderProgram(){
    id = glCreateProgram();
}
ShaderProgram::~ShaderProgram(){
    glDeleteProgram(id);
}

const unsigned int ShaderProgram::getID() const{
    return id;
}

void ShaderProgram::addShaderFromFile(const char* path){
    const char* it = path;

    for(it = path; *it != '.' && *it != '\0'; it++);

    if(*it == '.' && *(it+1) == 's' && *(it+2) == 'd'){ //filetype check
        
        int newShaderID;
        
        switch (*(it+3)){   //creates shader object based on the last character of the filetype
        case 'v': //.sdv for vertex shader
            newShaderID = glCreateShader(GL_VERTEX_SHADER);
            break;
        
        case 'f': //.sdf for fragment shader
            newShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            break;

        default:
            printf("ERROR. Unsuported shader type.\n");
        }

        char* shaderSource;
        std::ifstream shaderSourceFile;

        shaderSourceFile.open(path);

        if(shaderSourceFile.is_open()){

            //get file size in characters
            shaderSourceFile.seekg(0, std::ios::end);
            int count = shaderSourceFile.tellg();
            shaderSourceFile.seekg(0, std::ios::beg);

            //read based on file size;
            shaderSource = new char[count];
            shaderSourceFile.get(shaderSource, count, std::ios::end);
        }
        else
            printf("ERROR. could not open shader file.\n");

        glShaderSource(newShaderID, 1, &shaderSource, NULL);
        glCompileShader(newShaderID);

        //compile status check
        int success;
        char log[512];
        glGetShaderiv(newShaderID, GL_COMPILE_STATUS, &success);

        if(!success){
            glGetShaderInfoLog(newShaderID, 512, NULL, log);
            printf("ERROR. Could not compile shader: %s\n", log);
        }

        glAttachShader(id, newShaderID);

        glDeleteShader(newShaderID);
        delete[] shaderSource;
    }
    else{
        printf("ERROR. Wrong shader file type.\n");
    }
    
}

void ShaderProgram::link(){
    int success;
    char log[512];

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(id, 512, NULL, log);
        printf("ERROR. Could not link shader: %s\n", log);
    }
    
}

void ShaderProgram::bind(){
    glUseProgram(id);
}



void ShaderProgram::setUniform(const char* name, int x){
    glUniform1i(glGetUniformLocation(id, name), x);
}

void ShaderProgram::setUniform(const char* name, int x, int y){
    glUniform2i(glGetUniformLocation(id, name), x, y);
}

void ShaderProgram::setUniform(const char* name, int x, int y, int z){
    glUniform3i(glGetUniformLocation(id, name), x, y, z);
}

void ShaderProgram::setUniform(const char* name, float x){
    glUniform1f(glGetUniformLocation(id, name), x);
}

void ShaderProgram::setUniform(const char* name, float x, float y){
    glUniform2f(glGetUniformLocation(id, name), x, y);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z){
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}