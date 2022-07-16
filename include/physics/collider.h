#pragma once

#include "math/rectangle.h"
#include "math/vec2f.h"
#include "physics/colliderTypes.h"

//#define GET_COLLIDER_PARENT(type) (( type *)this->getParent())

//returns the parent object of a collider object. The type of the parent object must be specified.
#define GET_COLLIDER_PARENT(collider, type) (( type *)collider->getParent())

//defines an especific collider class for an especific parent class.
#define CREATE_COLLLIDABLE_TYPE(typename)   class typename : public Collider{\
                                                public:\
                                                    typename (void* parent, ColliderType type, const rectangle& hitbox = {0.0f, 0.0f, 0.0f, 0.0f}):\
                                                    Collider(parent, type, hitbox){}\
                                                    virtual void onCollide(Collider* other) override;\
                                            }

//if the signs are equal (0.0 counts as both)
#define CHECK_SIGN(a, b) ( a * b >= 0.0f)

/*A pattern for a class that will be attached to an object for it to collide. The onCollide(Collider* other)
function must be implemented through inheritance. All subclasses of Collider are referenced by the
collisionManager upon construction; the collision manager will call the onCollide function.*/
class Collider{
    private:
        void* parent;
        rectangle hitbox;
        bool active;
        ColliderType type;

    public:
        Collider(void* parent = nullptr, ColliderType type = ColliderType::defaultType, const rectangle& hitbox = {0.0f, 0.0f, 0.0f, 0.0f});
        virtual ~Collider();

        virtual void onCollide(Collider* other){}

        inline void activate(){active = true;}
        inline void deactivate(){active = false;}

        inline void setType(ColliderType type){this->type = type;}
        inline ColliderType getType() const{return type;}

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