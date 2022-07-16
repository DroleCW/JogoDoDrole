#pragma once

#include "math/vec2f.h"

/*Maps a region in the world to a region in the screen during render*/
class View{
    private:
        vec2f sourcePosition; //position in World Coordiates
        vec2f sourceSize; //width and height in World Coordiates

        vec2f targetPosition; //position in normalized screen coordinates
        vec2f targetSize;   //size in normalized screen coordinates

    public:
        /*
        sourcePosition: top left of the selected area of the world.
        sourceSize: size of the selected area on the world.
        these are measured in world units (pixels, most of the time).

        targetPosition: top left of the rectangle on the screen.
        targetSize: size of the rectangle on the screen.
        these are measured in screen coordinates. The top left of the screen is (-1, 1)
        and the bottom right is (1, -1).
        */
        View(const vec2f& sourcePosition = {0.0f, 0.0f}, const vec2f& sourceSize = {0.0f, 0.0f}, const vec2f& targetPosition = {-1.0f, 1.0f}, const vec2f& targetSize = {2.0f, 2.0f});
        ~View();

        inline void setSourcePosition(const vec2f& sourcePosition) {this->sourcePosition = sourcePosition;}
        inline void setSourceSize(const vec2f& sourceSize) {this->sourceSize = sourceSize;}

        inline void setTargetPosition(const vec2f& targetPosition) {this->targetPosition = targetPosition;}
        inline void setTargetSize(const vec2f& targetSize) {this->targetSize = targetSize;}

        inline vec2f getSourcePosition() const {return sourcePosition;}
        inline vec2f getSourceSize() const {return sourceSize;}

        inline vec2f getTargetPosition() const {return targetPosition;}
        inline vec2f getTargetSize() const {return targetSize;}

        inline vec2f getScalingFactor() const {return {targetSize.x/sourceSize.x, targetSize.y/sourceSize.y};}
};