#pragma once
#include "graphics/quad.h"


class Image: public Quad{
    
    private:
        

    public:
        Image(TextureLocation texture = NO_TEXTURE_LOCATION, bool autoindex = true);
        Image(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, bool autoindex = true);
        ~Image();
          
};