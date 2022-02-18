#include "graphics/text/text.h"

Text::Text(){
    pos = {0, 0};
    font = nullptr;
}

Text::~Text(){

}

void Text::setText(const std::string& text){

    if(font){
        characters.clear();

        content = text;
        vec2f origin(0.0f, 0.0f);
        for(auto i = content.begin(); i != content.end(); i++){
            characters.emplace_back(NO_TEXTURE_LOCATION, font->getCharPosition(*i), font->getCharSize(*i));
            characters.back().setPosition(pos+origin+font->getCharBearing(*i));
            characters.back().setSize(font->getCharSize(*i));
            origin.x += font->getCharAdvance(*i);
        }
    }
}

void Text::appendText(const std::string& text){

}

void Text::setFont(Font* font){
    this->font = font;
    if(characters.size())
        setText(content);
}

Image* Text::getNextCharacter(){
    if(index >= content.size())
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