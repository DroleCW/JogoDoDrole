#pragma once
#include "graphics/quad.h"
#include "graphics/textureLocations.h"

class Image: public Quad{
    
    private:
        TextureLocation texture;

    public:
        Image(TextureLocation texture = NO_TEXTURE_LOCATION);
        Image(TextureLocation texture, const vec2f& offset, const vec2f& totalSize);
        ~Image();

        inline void setTexture(TextureLocation texture){this->texture = texture;}
        inline TextureLocation getTexture() const{return texture;}
          
};