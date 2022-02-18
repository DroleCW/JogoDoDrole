#include "graphics/text/font.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "graphics/imageLoader/stb_image_write.h"

Font::Font(FT_Face face, int size): atlasTexture(){
    atlas = nullptr;
    this->face = face;
    this->size = size;
    generateAtlas();
}

Font::~Font(){

}

vec2f Font::getCharPosition(char c){
    return charPositions[c-32];
}

vec2f Font::getCharSize(char c){
    return charSizes[c-32];
}

vec2f Font::getCharBearing(char c){
    return charBearings[c-32];
}

float Font::getCharAdvance(char c){
    return charAdvances[c-32];
}

void Font::generateAtlas(){

    if(atlas)
        delete[] atlas;

    FT_Set_Pixel_Sizes(face, size, size);

    int w = 0, h = 0;
    for(char i = 32; i < 127; i++){
        FT_Load_Char(face, i, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
        charPositions[i-32] = {(float)w, 0};
        charSizes[i-32] = {face->glyph->bitmap.width, face->glyph->bitmap.rows};
        charBearings[i-32] = {face->glyph->metrics.horiBearingX/64.0, -face->glyph->metrics.horiBearingY/64.0};
        charAdvances[i-32] = face->glyph->metrics.horiAdvance/64.0;
        w += (float)face->glyph->bitmap.width;
        h = face->glyph->bitmap.rows > h ? (float)face->glyph->bitmap.rows : (float)h; //h = max(h, rows)
    }

    atlas = new unsigned char[4*w*h];

    int x = 0;
    for(char i = 32; i < 127; i++){
        FT_Load_Char(face, i, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
        int bitmapDataSize = face->glyph->bitmap.width*face->glyph->bitmap.rows;
        for(int i = 0; i < bitmapDataSize; i++){
            atlas[4*((x+i%face->glyph->bitmap.width)+w*(i/face->glyph->bitmap.width))] = face->glyph->bitmap.buffer[i];
            atlas[4*((x+i%face->glyph->bitmap.width)+w*(i/face->glyph->bitmap.width))+1] = face->glyph->bitmap.buffer[i];
            atlas[4*((x+i%face->glyph->bitmap.width)+w*(i/face->glyph->bitmap.width))+2] = face->glyph->bitmap.buffer[i];
            atlas[4*((x+i%face->glyph->bitmap.width)+w*(i/face->glyph->bitmap.width))+3] = face->glyph->bitmap.buffer[i];
        }
        x += face->glyph->bitmap.width;
    }

    atlasTexture.setData(atlas);
    atlasTexture.setHeight(h);
    atlasTexture.setWidth(w);
    atlasTexture.setChannels(4);
}