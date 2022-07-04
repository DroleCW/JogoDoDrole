#include "physics/collisionManager.h"

std::vector<Collidable*> CollisionManager::collidables;
std::unordered_multimap<Collidable*, Collidable*> CollisionManager::collisions;
Collidable* CollisionManager::indexedCollidable;
std::unordered_multimap<Collidable*, Collidable*>::local_iterator CollisionManager::indexedCollision;


CollisionManager::CollisionManager(){ 

}

CollisionManager::~CollisionManager(){

}

void CollisionManager::addCollidable(Collidable* collidable){
    collidables.push_back(collidable);
    collisions.clear();
}

void CollisionManager::removeCollidable(Collidable* collidable){
    for(auto i = collidables.begin(); i != collidables.end(); i++)
        if(*i == collidable){
            collidables.erase(i);
            break;
        }
}

void CollisionManager::checkCollision(Collidable* a, Collidable* b){

    if(!a->isActive() || !b->isActive()) return; //one of the collidables is inactive

    if(checkIntersection(a->getHitbox(), b->getHitbox())){

        //collisions.emplace(a, b);//log collisions
        //collisions.emplace(b, a);

        a->onCollide(b);//call events if any
        b->onCollide(a);

    }
}

bool CollisionManager::checkIntersection(const rectangle& a, const rectangle& b){
    if(a.x+a.w <= b.x || b.x+b.w <= a.x || a.y+a.h <= b.y || b.y+b.h <= a.y)
        return false;
    else
        return true;
    
}

vec2f CollisionManager::getOffset(const rectangle& a, const rectangle& b){
    vec2f offset;
    vec2f aCenter = {a.x+a.w/2, a.y+a.h/2};
    vec2f bCenter = {b.x+b.w/2, b.y+b.h/2};

    if(aCenter.x >= bCenter.x)
        offset.x = a.x-(b.x+b.w);
    else
        offset.x = a.x+a.w-b.x;


    if(aCenter.y >= bCenter.y)
        offset.y = a.y-(b.y+b.h);
    else
        offset.y = a.y+a.h-b.y;

    return offset;
}

vec2f CollisionManager::getCorrectionVel(const rectangle& a, const rectangle& b, const vec2f& vel){
    vec2f correction(0, 0);
    vec2f offset = getOffset(a, b);
    
    bool xPlausible = fabs(vel.x) - fabs(offset.x) >= 0;//a collision in x is plausible if the offset is smaller than the velocity in this axis
    bool yPlausible = fabs(vel.y) - fabs(offset.y) >= 0;//same for y
    //printf("    x is %f %f\n", fabs(vel.x) - fabs(offset.x), fabs(offset.x));
    //printf("    y is %f %f\n", fabs(vel.y) - fabs(offset.y), fabs(offset.y));

    if(xPlausible && !yPlausible)
        correction.x = -offset.x;
    else if(!xPlausible && yPlausible)
        correction.y = -offset.y;
    else{//if both (or none for some weird reason) are plausible, correct in the direction of the smallest offset
        /* if(fabs(offset.x) <= fabs(offset.y))
            correction.x = -offset.x;
        else
            correction.y = -offset.y; */
        correction.x = -offset.x;
        correction.y = -offset.y;
    }
    //printf("    correction got: %f, %f\n", correction.x, correction.y);
    return correction;
}

Collidable* CollisionManager::getNextCollision(Collidable* target){

    if(collisions.bucket_count() <= 1)
        return nullptr;
    if(target != indexedCollidable){
        indexedCollidable = target;
        indexedCollision = collisions.begin(collisions.bucket(target));
    }
    else if(indexedCollision == collisions.end(collisions.bucket(target)))
        indexedCollision++;

    if(indexedCollision == collisions.end(collisions.bucket(target)))
        return nullptr;
    
    else
        return indexedCollision->second;
    
}

void CollisionManager::pollAllCollisions(){
    collisions.clear();
    for(int i = 0; i < collidables.size(); i++)
        for(int j = i+1; j < collidables.size(); j++){
            checkCollision(collidables[i], collidables[j]);
        }
    indexedCollidable = nullptr;
}