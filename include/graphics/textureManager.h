#pragma once

#define MAX_BOUND_TEXTURES

#include "graphics/texture.h"
#include "graphics/textureLocations.h"

#include <fstream>
#include <vector>
#include <unordered_map>

/*Handles the loading and unloading of textures*/
class TextureManager{
    private:
        static Texture* loadedTextures[NUMBER_OF_TEXTURES]; //vector of all possible loaded textures
        static std::unordered_map<int, Texture*> atlas; //font atlas map for loaded fonts
        static char* texturePaths[NUMBER_OF_TEXTURES]; //paths of texture files
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

        /*fills the texturePaths vector using the contents of a file. The texture to TextureLocation index
        happens here*/
        static bool loadTexturePaths(const char* indicesFilePath);

        static inline int getLoadedTextures(){
            return totalLoadedTextures;
        }

};
