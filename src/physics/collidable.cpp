#include "physics/collidable.h"
#include "physics/collisionManager.h"

Collidable::Collidable(void* parent, CollidableType type, const rectangle& hitbox){
    this->parent = parent;
    setType(type);
    setHitbox(hitbox);
    activate();
    CollisionManager::addCollidable(this);
}

Collidable::~Collidable(){
    CollisionManager::removeCollidable(this);
}