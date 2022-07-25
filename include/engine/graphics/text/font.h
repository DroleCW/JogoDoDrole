#pragma once

#include "graphics/text/fontLocations.h"
#include "graphics/texture.h"

#include "graphics/text/ft2build.h"
#include "graphics/text/freetype/freetype.h"

#include "math/vec2f.h"

class Font{
    private:
        FT_Face face;
        int size;
        unsigned char* atlas;
        Texture atlasTexture;
        int atlasIndex;

        vec2f charPositions[127-32];
        vec2f charSizes[127-32];
        vec2f charBearings[127-32];
        float charAdvances[127-32];

    public:
        Font(FT_Face face = nullptr, int size = 0);
        ~Font();

        vec2f getCharPosition(char c);
        vec2f getCharSize(char c);
        vec2f getCharBearing(char c);
        float getCharAdvance(char c);

        inline int getAtlasIndex(){
            return atlasIndex;
        }

    private:
        void generateAtlas();
};