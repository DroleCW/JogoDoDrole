#include "graphics/sprite.h"
#include <stdio.h>

Sprite::Sprite(TextureLocation texture, bool autoIndex): Quad(autoIndex){
    setTexture(texture);
}

Sprite::Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, const vec2f& frameSize){
    setTexture(texture);
    generateFrames(offset, totalSize, frameSize);
}

Sprite::Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, short lines, short columns){
    setTexture(texture);
    generateFrames(offset, totalSize, lines, columns);
}

Sprite::~Sprite(){

}

void Sprite::generateFrames(const vec2f& offset, const vec2f& totalSize, const vec2f& frameSize){
    this->textureOffset = offset;
    this->textureSize = totalSize;
    this->frameSize = frameSize;
    this->setTextureSize(frameSize);
    this->setTexturePosition(offset);

    this->columns = totalSize.x/frameSize.x;
}

void Sprite::generateFrames(const vec2f& offset, const vec2f& totalSize, short lines, short columns){
    this->textureOffset = offset;
    this->frameSize = {(float)((int)totalSize.x/(int)columns), (float)((int)totalSize.y/(int)lines)};
    this->textureSize = {columns*frameSize.x, lines*frameSize.y};

    this->setTextureSize(frameSize);
    this->setTexturePosition(offset);

    this->columns = columns;
}

void Sprite::nextFrame(){
    moveTexture({frameSize.x, 0});
    if(getTexturePosition().x >= textureOffset.x + textureSize.x){  //check for end of line
        moveTexture({-textureSize.x, frameSize.y});
        if(getTexturePosition().y >= textureOffset.y + textureSize.y){ //check for end of atlas
            moveTexture({0.0f, -textureSize.y});
        }
    }
}

void Sprite::setFrame(short frameID){
    setTexturePosition({(frameID%columns)*frameSize.x, (frameID/columns)*frameSize.y});
}