#include "input/clickable.h"

Clickable::Clickable(const vec2f& pos, const vec2f& size){
    setClickBox(pos, size);
    hovering = false;
    clicked = false;
    enabled = true;
    InputManager::addClickable(this);
}

Clickable::~Clickable(){
    InputManager::removeClickable(this);
}

void Clickable::setClickBox(const vec2f& pos, const vec2f& size){
    this->pos = pos;
    this->size = size;
}