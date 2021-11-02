#pragma once

#include "graphics/quad.h"
#include "graphics/textureLocations.h"

class Sprite: public Quad{
    
    private:
        TextureLocation texture;
        vec2f textureOffset;    //position of the rectangle containing all quads 
        vec2f textureSize;      //size of the rectangle containing all quads 
        vec2f quadSize;         //size of the individual quad

        short columns;

    public:
        Sprite(TextureLocation texture = NO_TEXTURE_LOCATION);
        Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, const vec2f& quadSize);
        Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, short lines, short columns);
        ~Sprite();

        void generateQuads(const vec2f& offset, const vec2f& totalSize, const vec2f& quadSize);
        void generateQuads(const vec2f& offset, const vec2f& totalSize, short lines, short columns);

        void nextQuad();
        void setQuad(short quadID);

        inline TextureLocation getTexture() const{return texture;}

    
};