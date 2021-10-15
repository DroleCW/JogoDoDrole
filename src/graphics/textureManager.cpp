#include "graphics/textureManager.h"

TextureManager::TextureManager(){

}

TextureManager::~TextureManager(){
    

    for(auto textureIt = loadedTextures.begin(); textureIt != loadedTextures.end(); textureIt++)
        delete textureIt->second;

}

bool TextureManager::loadTexture(const char* path){

    auto textureIt = loadedTextures.find(path);

    if(textureIt == loadedTextures.end()){
        Texture* newTexture = new Texture();
        if(newTexture->loadFromFile(path)){
            loadedTextures.insert({path, newTexture});
            return true;
        }
        else{
            delete newTexture;
            return false;
        }
    }

    return true;
}

void TextureManager::unloadTexture(const char* path){

    auto textureIt = loadedTextures.find(path);

    if(textureIt != loadedTextures.end()){
        delete textureIt->second;
        loadedTextures.erase(textureIt);
    }
}

void TextureManager::bindTexture(const char* path, int slot){
    auto textureIt = loadedTextures.find(path);

    if(textureIt != loadedTextures.end())
       textureIt->second->bind(slot); 
    
}

Texture* TextureManager::getTexture(const char* path){
    auto textureIt = loadedTextures.find(path);

    if(textureIt != loadedTextures.end())
        return textureIt->second;
    else
        return nullptr;
}