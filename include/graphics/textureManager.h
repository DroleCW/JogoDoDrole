#pragma once

#define MAX_BOUND_TEXTURES

#include "graphics/texture.h"
#include "graphics/textureLocations.h"

#include <fstream>
#include <vector>

class TextureManager{
    private:
        static Texture* loadedTextures[NUMBER_OF_TEXTURES];
        static char* texturePaths[NUMBER_OF_TEXTURES];
        static int totalLoadedTextures;

        TextureManager();
        ~TextureManager();
    public:
        
        static void init();
        static void terminate();

        static bool loadTexture(TextureLocation textureIndex);
        static void unloadTexture(TextureLocation textureIndex);
        static void bindTexture(TextureLocation textureIndex, int slot);
        static Texture* getTexture(TextureLocation textureIndex);

        static bool loadTexturePaths(const char* indicesFilePath);

        static inline int getLoadedTextures(){
            return totalLoadedTextures;
        }

};
