#pragma once


/*List of collider types in the game. Every collider should have a type so that the collisions can
be solved accordingly within each class*/
enum ColliderType{
    defaultType = 0,
    testSprite,
    testImage
};