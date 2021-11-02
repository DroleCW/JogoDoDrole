#include "graphics/sprite.h"
#include <stdio.h>

Sprite::Sprite(TextureLocation texture){
    this->texture = texture;
}

Sprite::Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, const vec2f& quadSize){
    this->texture = texture;
    generateQuads(offset, totalSize, quadSize);
}

Sprite::Sprite(TextureLocation texture, const vec2f& offset, const vec2f& totalSize, short lines, short columns){
    this->texture = texture;
    generateQuads(offset, totalSize, lines, columns);
}

Sprite::~Sprite(){

}

void Sprite::generateQuads(const vec2f& offset, const vec2f& totalSize, const vec2f& quadSize){
    this->textureOffset = offset;
    this->textureSize = totalSize;
    this->quadSize = quadSize;
    this->setTextureSize(quadSize);
    this->setTexturePosition(offset);

    this->columns = totalSize.x/quadSize.x;
}

void Sprite::generateQuads(const vec2f& offset, const vec2f& totalSize, short lines, short columns){
    this->textureOffset = offset;
    this->quadSize = {(float)((int)totalSize.x/(int)columns), (float)((int)totalSize.y/(int)lines)};
    this->textureSize = {columns*quadSize.x, lines*quadSize.y};

    this->setTextureSize(quadSize);
    this->setTexturePosition(offset);

    this->columns = columns;
}

void Sprite::nextQuad(){
    moveTexture({quadSize.x, 0});
    if(getTexturePosition().x >= textureOffset.x + textureSize.x){  //check for end of line
        moveTexture({-textureSize.x, quadSize.y});
        if(getTexturePosition().y >= textureOffset.y + textureSize.y){ //check for end of atlas
            moveTexture({0.0f, -textureSize.y});
        }
    }
}

void Sprite::setQuad(short quadID){
    setTexturePosition({(quadID%columns)*quadSize.x, (quadID/columns)*quadSize.y});
}