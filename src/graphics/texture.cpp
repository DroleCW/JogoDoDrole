#include "graphics/texture.h"
#include "graphics/imageLoader/stb_image.h"
#include <glad/glad.h>

Texture::Texture():id(-1){
    width = -1;
    height = -1;
    channels = -1;
    
    textureObject = 0;

    data = nullptr;
}

Texture::Texture(int id):id(id){
    width = 0;
    height = 0;
    channels = 0;

    glGenTextures(1, &textureObject);

    data = nullptr;
}

Texture::Texture(int id, const char* path):id(id){
    width = 0;
    height = 0;
    channels = 0;

    glGenTextures(1, &textureObject);

    data = nullptr;

    loadFromFile(path);
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
        printf("ERROR: could not load texture. ID: %d\n", id);
        return false;
    }
}

int Texture::getId() const{
    return id;
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
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}