#pragma once
#include "graphics/quad.h"

//a static image. meant to save data when objects don't need to be animated.
class Image: public Quad{
    
    private:
        

    public:
        Image(TextureLocation texture = NO_TEXTURE_LOCATION, bool autoindex = true);
        Image(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, bool autoindex = true);
        ~Image();
          
};