#pragma once
#include "graphics/quad.h"


class Image: public Quad{
    
    private:
        

    public:
        Image(TextureLocation texture = NO_TEXTURE_LOCATION);
        Image(TextureLocation texture, const vec2f& offset, const vec2f& totalSize);
        ~Image();
          
};