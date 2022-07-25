#include "graphics/text/text.h"
#include "graphics/graphicManager.h"

Text::Text(){
    pos = {0, 0};
    size = {0, 0};
    cursor = {0.0f, 0.0f};
    color = {1.0f, 1.0f, 1.0f, 1.0f};
    font = nullptr;
    lineSpacing = 0;
    layer = 0;
    visible = true;
    GraphicManager::addText(this);
}

Text::~Text(){
    characters.clear();
    GraphicManager::removeText(this);
}

void Text::setText(const std::string& text){
    size = {0.0f, 0.0f};
    characters.clear();
    content.clear();
    cursor = {0.0f, 0.0f};
    appendText(text);
}

void Text::appendText(const std::string& text){
    vec2f sizeDelta(0, 0);
    content += text;
    if(font){
        for(auto i = text.begin(); i != text.end(); i++){
            if((*i) == '\n'){
                cursor.y += lineSpacing;
                cursor.x = 0.0f;

                size.y += sizeDelta.y;
                size.x = size.x < sizeDelta.x ? sizeDelta.x : size.x; 
                continue;
            }

            characters.emplace_back(NO_TEXTURE_LOCATION, font->getCharPosition(*i), font->getCharSize(*i), false);
            characters.back().setPosition(pos+cursor+font->getCharBearing(*i));
            characters.back().setSize(font->getCharSize(*i));
            characters.back().setColor(color);
            characters.back().setLayer(layer);
            characters.back().setTexture((TextureLocation)font->getAtlasIndex());
            cursor.x += font->getCharAdvance(*i);

            sizeDelta.x += font->getCharAdvance(*i);
            sizeDelta.y = sizeDelta.y < font->getCharSize(*i).y ? font->getCharSize(*i).y : sizeDelta.y;
        }
        size.y += sizeDelta.y;
        size.x = size.x < sizeDelta.x ? sizeDelta.x : size.x; 
    }
}

void Text::setFont(Font* font){
    this->font = font;
    if(characters.size())
        setText(content);
}

Image* Text::getNextCharacter(){
    if(index >= characters.size())
        return nullptr;
    return &characters[index++];
}

void Text::resetIterator(){
    index = 0;
}

void Text::setPosition(vec2f pos){
    vec2f delta = pos - this->pos;
    for(auto i = characters.begin(); i != characters.end(); i++){
        i->move(delta);
    }
}

void Text::move(vec2f delta){
    for(auto i = characters.begin(); i != characters.end(); i++){
        i->move(delta);
    }
}

void Text::setColor(vec4f colorRGBA){
    color = colorRGBA;
    for(auto i = characters.begin(); i != characters.end(); i++){
        i->setColor(colorRGBA);
    }
}

void Text::setLayer(float layer){
    this->layer = layer;
    for(auto i = characters.begin(); i != characters.end(); i++){
        i->setLayer(layer);
    }
}
