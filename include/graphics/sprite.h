#pragma once

#include "graphics/quad.h"
#include "graphics/textureLocations.h"


/*A frame with animation function*/
class Sprite: public Quad{
    
    private:
        vec2f textureOffset;    //position of the rectangle containing all frames 
        vec2f textureSize;      //size of the rectangle containing all frames 
        vec2f frameSize;        //size of the individual frame

        short columns;

    public:
        Sprite(TextureLocation texture = NO_TEXTURE_LOCATION, bool autoIndex = true);

        //creates a sprite with an specific texture and provides information for frame separation.
        Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, const vec2f& frameSize);
        Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, short lines, short columns);
        
        ~Sprite();

        /*Generate the animation frames of the sprite.
        offset: top left corner of the group of frames in the texture.
        totalSize: total size of the group of frames in the texture.
        frameSize: size of the individual frames in the texture.*/
        void generateFrames(const vec2f& offset, const vec2f& totalSize, const vec2f& frameSize);

        /*Generate the animation frames of the sprite.
        offset: top left corner of the group of frames in the texture.
        totalSize: total size of the group of frames in the texture.
        lines: number of lines of frames in the texture.
        columns: number of columns of frames in the texture.*/
        void generateFrames(const vec2f& offset, const vec2f& totalSize, short lines, short columns);

        void nextFrame();
        void setFrame(short frameID);

};