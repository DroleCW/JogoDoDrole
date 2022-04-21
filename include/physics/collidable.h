#pragma once

#include "math/rectangle.h"
#include "math/vec2f.h"
#include "physics/collidableTypes.h"

class Collidable{
    private:
        rectangle hitbox;
        bool active;
        CollidableType type;
        int childCount;
        Collidable* childreen;

    public:
        Collidable(CollidableType type = defaultType, const rectangle& hitbox = {0.0f, 0.0f, 0.0f, 0.0f});
        ~Collidable();

        inline void setChildreen(Collidable* childreenArray, int size){
            childreen = childreenArray;
            childCount = size;
        }

        inline Collidable* getChildreen() const{
            return childreen;
        }

        inline int getChildreenCount() const{
            return childCount;
        }

        inline void activate(){active = true;}
        inline void deactivate(){active = false;}

        inline void setType(CollidableType type){this->type = type;}
        inline CollidableType getType() const{return type;}

        inline void setHitbox(const rectangle& hitbox){
            this->hitbox = hitbox;
        }
        inline const rectangle& getHitbox() const{
            return hitbox;
        }

        inline bool isActive() const {return active;}

        inline void setPosition(const vec2f& pos){
            hitbox.x = pos.x;
            hitbox.y = pos.y;
        }

        inline void move(const vec2f& delta){
            hitbox.x += delta.x;
            hitbox.y += delta.y;
        }

        inline void setSize(const vec2f& size){
            hitbox.w = size.x;
            hitbox.h = size.y;
        }


};