#include "physics/collidable.h"

Collidable::Collidable(CollidableType type, const rectangle& hitbox){
    childCount = 0;
    childreen = nullptr;
    setType(type);
    setHitbox(hitbox);
    activate();
}

Collidable::~Collidable(){

}