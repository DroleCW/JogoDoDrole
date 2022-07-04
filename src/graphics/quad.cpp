#include "graphics/quad.h"
#include "graphics/graphicManager.h"

Quad::Quad(bool autoIndex){
    visible = true;
    for(int i = 0; i < 4; i++){
        vertices[i] = { 
                        {0.0f, 0.0f},//position
                        0.0f,
                        {1.0f, 1.0f, 1.0f, 1.0f},//color (opaque white)
                        {0.0f, 0.0f}//texture coordinates
                      };
    }
    if(autoIndex)
        GraphicManager::addQuad(this);
    
}


Quad::~Quad(){
    GraphicManager::removeQuad(this);
}

void Quad::setPosition(const vec2f& pos){
    vec2f size = vertices[2].position - vertices[0].position;

    vertices[0].position = pos;
    vertices[1].position = {pos.x + size.x, pos.y};
    vertices[2].position = {pos.x + size.x, pos.y + size.y};
    vertices[3].position = {pos.x, pos.y + size.y};

    /* printf("quad pos:"
            "   %f, %f\n"
            "   %f, %f\n"
            "   %f, %f\n"
            "   %f, %f\n",
            vertices[0].position.x, vertices[0].position.y,
            vertices[1].position.x, vertices[1].position.y,
            vertices[2].position.x, vertices[2].position.y,
            vertices[3].position.x, vertices[3].position.y); */
}

void Quad::move(const vec2f& delta){
    vertices[0].position += delta;
    vertices[1].position += delta;
    vertices[2].position += delta;
    vertices[3].position += delta;
}

void Quad::setSize(const vec2f& size){
    vertices[1].position = {vertices[0].position.x + size.x, vertices[0].position.y};
    vertices[2].position = {vertices[0].position.x + size.x, vertices[0].position.y + size.y};
    vertices[3].position = {vertices[0].position.x, vertices[0].position.y + size.y};
}

vec2f Quad::getSize() const{
    return vertices[2].position - vertices[0].position;
}

void Quad::scale(float scalar){
    vertices[1].position = vertices[0].position + scalar*(vertices[1].position - vertices[0].position);
    vertices[2].position = vertices[0].position + scalar*(vertices[2].position - vertices[0].position);
    vertices[3].position = vertices[0].position + scalar*(vertices[3].position - vertices[0].position);
}

void Quad::setWidth(float width){
    vertices[1].position.x = vertices[0].position.x + width;
    vertices[2].position.x = vertices[0].position.x + width;
}

void Quad::setHeight(float height){
    vertices[2].position.y = vertices[0].position.y + height;
    vertices[3].position.y = vertices[0].position.y + height;
}

void Quad::setLayer(int layer){
    vertices[0].layer = layer;
    vertices[1].layer = layer;
    vertices[2].layer = layer;
    vertices[3].layer = layer;
}

void Quad::setTexturePosition(const vec2f& pos){
    vec2f size = vertices[2].textureCoord - vertices[0].textureCoord;

    vertices[0].textureCoord = pos;
    vertices[1].textureCoord = {pos.x + size.x, pos.y};
    vertices[2].textureCoord = {pos.x + size.x, pos.y + size.y};
    vertices[3].textureCoord = {pos.x, pos.y + size.y};

}

void Quad::moveTexture(const vec2f& delta){
    vertices[0].textureCoord += delta;
    vertices[1].textureCoord += delta;
    vertices[2].textureCoord += delta;
    vertices[3].textureCoord += delta;
}

void Quad::setTextureSize(const vec2f& size){
    vertices[1].textureCoord = {vertices[0].textureCoord.x + size.x, vertices[0].textureCoord.y};
    vertices[2].textureCoord = {vertices[0].textureCoord.x + size.x, vertices[0].textureCoord.y + size.y};
    vertices[3].textureCoord = {vertices[0].textureCoord.x, vertices[0].textureCoord.y + size.y};
}

void Quad::setTextureWidth(float width){
    vertices[1].textureCoord.x = vertices[0].textureCoord.x + width;
    vertices[2].textureCoord.x = vertices[0].textureCoord.x + width;
}

void Quad::setTextureHeight(float height){
    vertices[2].textureCoord.y = vertices[0].textureCoord.y + height;
    vertices[3].textureCoord.y = vertices[0].textureCoord.y + height;
}

void Quad::setColor(vec4f colorRGBA){
    vertices[0].color = colorRGBA;
    vertices[1].color = colorRGBA;
    vertices[2].color = colorRGBA;
    vertices[3].color = colorRGBA;
}

const float* Quad::getDataf() const{
    return (float*)vertices;
}
