#include "graphics/texture.h"
#include "graphics/imageLoader/stb_image.h"
#include <glad/glad.h>

Texture::Texture(const char* path){
    width = 0;
    height = 0;
    channels = 0;
    
    textureObject = 0;

    data = nullptr;

    glGenTextures(1, &textureObject);

    if(path){
        loadFromFile(path);
    }
}

Texture::~Texture(){
    if(data){
        stbi_image_free(data);
        glDeleteTextures(1, &textureObject);
    }
}

bool Texture::loadFromFile(const char* path){

    if(data){
        stbi_image_free(data);
        data = nullptr;
    }

    data = stbi_load(path, &width, &height, &channels, 0);

    if(data)
        return true;
    else{
        printf("ERROR: could not load texture.");
        return false;
    }
}

void Texture::setData(unsigned char* data){
    if(this->data != data)
        delete this->data;
    this->data = data;
}

int Texture::getWidth() const{
    return width;
}

int Texture::getHeight() const{
    return height;
}

int Texture::getChannels() const{
    return channels;
}

void Texture::bind(int slot) const{

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_RECTANGLE, textureObject);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(channels == 4){
        glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    if(channels == 3){
        glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if(channels == 1){
        glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RED, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
    }
}