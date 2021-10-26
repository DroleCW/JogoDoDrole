#pragma once

#define MAX_BOUND_TEXTURES

#include "graphics/texture.h"
#include "graphics/textureLocations.h"

#include <fstream>
#include <vector>

class TextureManager{
    private:
        Texture* loadedTextures[NUMBER_OF_TEXTURES];
        char* texturePaths[NUMBER_OF_TEXTURES];
    
    public:
        TextureManager();
        ~TextureManager();

        bool loadTexture(TextureLocation textureIndex);
        void unloadTexture(TextureLocation textureIndex);
        void bindTexture(TextureLocation textureIndex, int slot);
        Texture* getTexture(TextureLocation textureIndex);

        bool loadTexturePaths(const char* indicesFilePath);

};
