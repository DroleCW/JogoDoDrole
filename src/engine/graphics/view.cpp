#include "graphics/view.h"
#include "stdio.h"

View::View(const vec2f& sourcePosition, const vec2f& sourceSize, const vec2f& targetPosition, const vec2f& targetSize){
    setSourcePosition(sourcePosition);
    setSourceSize(sourceSize);

    setTargetPosition(targetPosition);
    setTargetSize(targetSize);

}

View::~View(){

}
