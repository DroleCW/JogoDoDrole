#pragma once

#include "math/rectangle.h"
#include "math/vec2f.h"
#include "physics/collidableTypes.h"

//#define GET_COLLIDABLE_PARENT(type) (( type *)this->getParent())
#define GET_COLLIDABLE_PARENT(collidable, type) (( type *)collidable->getParent())

#define CREATE_COLLLIDABLE_TYPE(typename)   class typename : public Collidable{\
                                                public:\
                                                    typename (void* parent, CollidableType type, const rectangle& hitbox = {0.0f, 0.0f, 0.0f, 0.0f}):\
                                                    Collidable(parent, type, hitbox){}\
                                                    virtual void onCollide(Collidable* other) override;\
                                            }

//if the signs are equal (0.0 counts as both)
#define CHECK_SIGN(a, b) ( a * b >= 0.0f)

class Collidable{
    private:
        void* parent;
        rectangle hitbox;
        bool active;
        CollidableType type;

    public:
        Collidable(void* parent = nullptr, CollidableType type = CollidableType::defaultType, const rectangle& hitbox = {0.0f, 0.0f, 0.0f, 0.0f});
        virtual ~Collidable();

        virtual void onCollide(Collidable* other){}

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

        inline void setParent(void* parent){
            this->parent = parent;
        }

        inline void* getParent() const{
            return parent;
        }
};