#pragma once

#define MAX_BOUND_TEXTURES

#include "graphics/texture.h"
#include "graphics/textureLocations.h"

#include <fstream>
#include <vector>
#include <unordered_map>

class TextureManager{
    private:
        static Texture* loadedTextures[NUMBER_OF_TEXTURES];
        static std::unordered_map<int, Texture*> atlas;
        static char* texturePaths[NUMBER_OF_TEXTURES];
        static int totalLoadedTextures;

        TextureManager();
        ~TextureManager();
    public:
        
        static void init();
        static void terminate();

        static bool loadTexture(TextureLocation textureIndex);
        static void unloadTexture(TextureLocation textureIndex);

        static int addAtlas(Texture* atlasTexture);
        static void removeAtlas(int atlasIndex);
        static Texture* getAtlas(int atlasIndex);

        static void bindTexture(TextureLocation textureIndex, int slot);
        static Texture* getTexture(TextureLocation textureIndex);

        static bool loadTexturePaths(const char* indicesFilePath);

        static inline int getLoadedTextures(){
            return totalLoadedTextures;
        }

};
