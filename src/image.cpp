#include "graphics/image.h"

Image::Image(TextureLocation texture = NO_TEXTURE_LOCATION){

    setTexturePosition({0.0f, 0.0f});
    setTextureSize({0.0f, 0.0f});

    setPosition({0.0f, 0.0f});
    setSize({0.0f, 0.0f});

    this->texture = texture;
}

Image::Image(TextureLocation texture, const vec2f& offset, const vec2f& totalSize){
    setTexturePosition(offset);
    setTextureSize(totalSize);

    setPosition({0.0f, 0.0f});
    setSize(totalSize);

    this->texture = texture;

}

Image::~Image(){

}