#pragma once
#include "graphics/image.h"

class Particle: public Image{

    private:
        vec2f velocity;
        float lifetime;
        float scalingFactor;
        bool isAlive;

    public:
        Particle(TextureLocation textureIndex = NO_TEXTURE_LOCATION);
        ~Particle();

        inline void setVelocity(vec2f velocity){
            this->velocity = velocity;
        }

        inline void setLifetime(float lifetime){
            isAlive = true;
            this->lifetime = lifetime;
        }

        inline void setScalingFactor(float scalingFactor){
            this->scalingFactor = scalingFactor;
        }

        inline bool getIsAlive(){
            return isAlive;
        }

        bool update(float dt); //returns true if the particle is still alive

};