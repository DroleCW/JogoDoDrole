#pragma once
#include "graphics/particles/particle.h"
#include "graphics/textureLocations.h"
#include "math/vec2f.h"

#define MAX_LIVING_PARTICLES 100

class ParticleSystem{
    private:
        TextureLocation texture;
        vec2f position;
        vec2f velocity;

        vec2f lowPositionLimit, highPositionLimit;
        vec2f lowVelocityLimit, highVelocityLimit;

        vec2f lowSizeLimit, highSizeLimit;
        bool keepSizeRatio;

        float lowLifetime, highLifetime;

        Particle* particles;
        int it;
        int insertionIt; //used to speed up the emission of new particles
        int livingParticles;

    public:
        ParticleSystem();
        ~ParticleSystem();

        void update(float dt);

        void setTexture(TextureLocation texture);
        void setTexturePosition(vec2f texturePosition);
        void setTextureSize(vec2f textureSize);
        void setColor(vec4f color);
        void setLayer(int layer);

        inline void setPosition(vec2f& position){
            this->position = position;
        }
        inline void setPosition(vec2f&& position){
            this->position = position;
        }

        inline void setVelocity(vec2f velocity){
            this->velocity = velocity;
        }
        
        inline void setPositionRange(vec2f lowerLimit, vec2f higherLimit){
            lowPositionLimit = lowerLimit;
            highPositionLimit = higherLimit;
        }

        inline void setVelocityRange(vec2f lowerLimit, vec2f higherLimit){
            lowVelocityLimit = lowerLimit;
            highVelocityLimit = higherLimit;
        }

        inline void setSizeRange(vec2f lowerLimit, vec2f higherLimit, bool keepRatio){
            keepSizeRatio = keepRatio;
            lowSizeLimit = lowerLimit;
            highSizeLimit = higherLimit;
        }

        void setScalingFactor(float scalingFactor);

        inline void setLifetimeRange(float lowerLimit, float higherLimit){
            lowLifetime = lowerLimit;
            highLifetime = higherLimit;
        }

        inline TextureLocation getTexture(){
            return texture;
        }

        inline void resetIterator(){
            it = 0;
        }

        Particle* getNextLivingParticle();

        void emit();
        void emit(int repeat);
};