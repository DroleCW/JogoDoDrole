#include "physics/collider.h"
#include "physics/collisionManager.h"

Collider::Collider(void* parent, ColliderType type, const rectangle& hitbox){
    this->parent = parent;
    setType(type);
    setHitbox(hitbox);
    activate();
    CollisionManager::addCollider(this);
}

Collider::~Collider(){
    CollisionManager::removeCollider(this);
}