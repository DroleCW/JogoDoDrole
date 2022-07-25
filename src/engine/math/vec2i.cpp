#include "math/vec2i.h"

vec2i::vec2i(){
    
}

vec2i::vec2i(int x, int y):x(x), y(y){
    
}

vec2i::~vec2i(){

}

float vec2i::length() const{
    return sqrt(x*x+y*y);
}

void vec2i::operator=(const vec2i& attrib){
    x = attrib.x;
    y = attrib.y;
}

void vec2i::operator+=(const vec2i& attrib){
    x += attrib.x;
    y += attrib.y;
}

void vec2i::operator-=(const vec2i& attrib){
    x -= attrib.x;
    y -= attrib.y;
}

const vec2i vec2i::operator*(int scalar) const{
    return vec2i(x*scalar, y*scalar);
}

const vec2i vec2i::operator/(int scalar) const{
    return vec2i(x/scalar, y/scalar);
}

const vec2i operator+(const vec2i& first, const vec2i& second){
    vec2i sum(first.x+second.x, first.y+second.y);
    return sum;
}

const vec2i operator-(const vec2i& first, const vec2i& second){
    vec2i sub(first.x-second.x, first.y-second.y);
    return sub;
}

const vec2i operator*(int scalar, const vec2i& vec){
    return vec2i(vec.x*scalar, vec.y*scalar);
}

const vec2i operator/(int scalar, const vec2i& vec){
    return vec2i(vec.x/scalar, vec.y/scalar);
}