#pragma once

#include "physics/collider.h"
#include <unordered_map>
#include <vector>

class Collider;

class CollisionManager{
    private:
        CollisionManager();
        ~CollisionManager();
        static std::unordered_multimap<Collider*, Collider*> collisions;
        static std::vector<Collider*> colliders;
        static Collider* indexedCollider;
        static std::unordered_multimap<Collider*, Collider*>::local_iterator indexedCollision;

    public:
        static void addCollider(Collider*);
        static void removeCollider(Collider*);

        //checks and logs whether a collision happened between colliders a and b
        //all found collisions are logged in the collisions map. 
        static void checkCollision(Collider* a, Collider* b);

        //checks whether a rectangle intersects another
        static bool checkIntersection(const rectangle& a, const rectangle& b);

        //returns how far in is 'a' into 'b', it is always the smallest possible answer
        static vec2f getOffset(const rectangle& a, const rectangle& b);

        //returns how an intersection should be corrected based on a previous displacement vector (vel)
        static vec2f getCorrectionVel(const rectangle& a, const rectangle& b, const vec2f& vel);

        //returns the next collider that collided with target
        static Collider* getNextCollision(Collider* target);

        //clears and refills the collision log
        static void pollAllCollisions();

};