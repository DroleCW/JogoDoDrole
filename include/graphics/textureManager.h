#pragma once

#include "graphics/texture.h"

#include <map>

class TextureManager{
    private:
        std::map<const char*, Texture*> loadedTextures;
    
    public:
        TextureManager();
        ~TextureManager();

        bool loadTexture(const char* path);
        void unloadTexture(const char* path);
        void bindTexture(const char* path, int slot);
        Texture* getTexture(const char* path);

};
