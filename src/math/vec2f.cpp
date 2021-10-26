#include "math/vec2f.h"

vec2f::vec2f(){
    
}

vec2f::vec2f(float x, float y):x(x), y(y){
    
}

vec2f::~vec2f(){

}

float vec2f::length() const{
    return sqrt(x*x+y*y);
}

void vec2f::operator=(const vec2f& attrib){
    x = attrib.x;
    y = attrib.y;
}

void vec2f::operator+=(const vec2f& attrib){
    x += attrib.x;
    y += attrib.y;
}

void vec2f::operator-=(const vec2f& attrib){
    x -= attrib.x;
    y -= attrib.y;
}

const vec2f vec2f::operator*(float scalar) const{
    return vec2f(x*scalar, y*scalar);
}

const vec2f vec2f::operator/(float scalar) const{
    return vec2f(x/scalar, y/scalar);
}

const vec2f operator+(const vec2f& first, const vec2f& second){
    vec2f sum(first.x+second.x, first.y+second.y);
    return sum;
}

const vec2f operator-(const vec2f& first, const vec2f& second){
    vec2f sub(first.x-second.x, first.y-second.y);
    return sub;
}

const vec2f operator*(float scalar, const vec2f& vec){
    return vec2f(vec.x*scalar, vec.y*scalar);
}

const vec2f operator/(float scalar, const vec2f& vec){
    return vec2f(vec.x/scalar, vec.y/scalar);
}