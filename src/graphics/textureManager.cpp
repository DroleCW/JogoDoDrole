#include "graphics/textureManager.h"

TextureManager::TextureManager(){
    for(int i = 1; i < NUMBER_OF_TEXTURES; i++)
        loadedTextures[i] = nullptr;

    loadTexturePaths(TEXTURE_INDEX_FILE);

}

TextureManager::~TextureManager(){
    

    for(int i = 1; i < NUMBER_OF_TEXTURES; i++)
        if(loadedTextures[i])
            delete loadedTextures[i];

    for(int i = 1; i < NUMBER_OF_TEXTURES; i++)
        if(texturePaths[i])
            delete[] texturePaths[i];

}

bool TextureManager::loadTexture(TextureLocation textureIndex){
    if(loadedTextures[textureIndex] == nullptr){
        Texture* newTexture = new Texture();
        if(newTexture->loadFromFile(texturePaths[textureIndex])){
            loadedTextures[textureIndex] = newTexture;
            return true;
        }
        else{
            delete newTexture;
            return false;
        }
    }

    return true;
}

void TextureManager::unloadTexture(TextureLocation textureIndex){

    if(loadedTextures[textureIndex]){
        delete loadedTextures[textureIndex];
        loadedTextures[textureIndex] = nullptr;
    }
}

void TextureManager::bindTexture(TextureLocation textureIndex, int slot){
    loadedTextures[textureIndex]->bind(slot); 
}

Texture* TextureManager::getTexture(TextureLocation textureIndex){
    return loadedTextures[textureIndex];
}

bool TextureManager::loadTexturePaths(const char* indicesFilePath){

    std::ifstream textureIndicesFile;

    textureIndicesFile.open(indicesFilePath);

    for(int i = 1; i < NUMBER_OF_TEXTURES; i++)
        texturePaths[i] = new char[MAX_TEXTURE_PATH_SIZE];


    if(textureIndicesFile.is_open()){
        int index = 1;
        while (textureIndicesFile.peek() != EOF && index < NUMBER_OF_TEXTURES){
            textureIndicesFile.ignore(5, ' ');
            textureIndicesFile.getline(texturePaths[index], 40);
            index++;
        }
        if(index == NUMBER_OF_TEXTURES)
            return true;
        else{
            printf("ERROR: Failure to load all texture files\n");
            return false; 
        }
    }
    else{
        printf("ERROR: Could not load texture paths.\n");
        return false;
    }
}