#include "graphics/image.h"

Image::Image(TextureLocation texture, bool autoIndex): Quad(autoIndex){

    setTexturePosition({0.0f, 0.0f});
    setTextureSize({0.0f, 0.0f});

    setPosition({0.0f, 0.0f});
    setSize({0.0f, 0.0f});

    setTexture(texture);
}

Image::Image(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, bool autoIndex): Quad(autoIndex){
    setTexturePosition(offset);
    setTextureSize(totalSize);

    setPosition({0.0f, 0.0f});
    setSize(totalSize);

    setTexture(texture);
}

Image::~Image(){
    //printf("        destroying image\n");
}