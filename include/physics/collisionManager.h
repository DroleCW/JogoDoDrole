#pragma once

#include "physics/collidable.h"
#include <unordered_map>
#include <vector>

class Collidable;

class CollisionManager{
    private:
        CollisionManager();
        ~CollisionManager();
        static std::unordered_multimap<Collidable*, Collidable*> collisions;
        static std::vector<Collidable*> collidables;
        static Collidable* indexedCollidable;
        static std::unordered_multimap<Collidable*, Collidable*>::local_iterator indexedCollision;

    public:
        static void addCollidable(Collidable*);
        static void removeCollidable(Collidable*);

        //checks and logs whether a collision happened between collidables a and b
        //all found collisions are logged in the collisions map. 
        static void checkCollision(Collidable* a, Collidable* b);

        //checks whether a rectangle intersects another
        static bool checkIntersection(const rectangle& a, const rectangle& b);

        //returns how far in is 'a' into 'b', it is always the smallest possible answer
        static vec2f getOffset(const rectangle& a, const rectangle& b);

        //returns how an intersection should be corrected based on a previous displacement vector (vel)
        static vec2f getCorrectionVel(const rectangle& a, const rectangle& b, const vec2f& vel);

        //returns the next collidable that collided with target
        static Collidable* getNextCollision(Collidable* target);

        //clears and refills the collision log
        static void pollAllCollisions();

};