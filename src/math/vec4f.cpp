#include "math/vec4f.h"

vec4f::vec4f(){
    
}

vec4f::vec4f(float x, float y, float z, float w):x(x), y(y), z(z), w(w){
    
}

vec4f::~vec4f(){

}

float vec4f::length() const{
    return sqrt(x*x+y*y+z*z+w*w);
}

void vec4f::operator=(const vec4f& attrib){
    x = attrib.x;
    y = attrib.y;
    z = attrib.z;
    w = attrib.w;
}

void vec4f::operator+=(const vec4f& attrib){
    x += attrib.x;
    y += attrib.y;
    z += attrib.z;
    w += attrib.w;
}

void vec4f::operator-=(const vec4f& attrib){
    x -= attrib.x;
    y -= attrib.y;
    z -= attrib.z;
    w -= attrib.w;
}

const vec4f vec4f::operator*(float scalar) const{
    return vec4f(x*scalar, y*scalar, z*scalar, w*scalar);
}

const vec4f vec4f::operator/(float scalar) const{
    return vec4f(x/scalar, y/scalar, z/scalar, w/scalar);
}

const vec4f operator+(const vec4f& first, const vec4f& second){
    vec4f sum(first.x+second.x, first.y+second.y, first.z+second.z, first.w+second.w);
    return sum;
}

const vec4f operator-(const vec4f& first, const vec4f& second){
    vec4f sub(first.x-second.x, first.y-second.y, first.z-second.z, first.w-second.w);
    return sub;
}

const vec4f operator*(float scalar, const vec4f& vec){
    return vec4f(vec.x*scalar, vec.y*scalar, vec.z*scalar, vec.w*scalar);
}

const vec4f operator/(float scalar, const vec4f& vec){
    return vec4f(vec.x/scalar, vec.y/scalar, vec.z/scalar, vec.w/scalar);
}