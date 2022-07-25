#include "input/clickBox.h"

ClickBox::ClickBox(const vec2f& pos, const vec2f& size){
    setBox(pos, size);
    hovering = false;
    clicked = false;
    enabled = true;
    InputManager::addClickBox(this);
}

ClickBox::~ClickBox(){
    InputManager::removeClickBox(this);
}

void ClickBox::setBox(const vec2f& pos, const vec2f& size){
    this->pos = pos;
    this->size = size;
}