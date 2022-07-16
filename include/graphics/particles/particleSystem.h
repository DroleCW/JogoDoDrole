#pragma once
#include "graphics/particles/particle.h"
#include "graphics/textureLocations.h"
#include "math/vec2f.h"

#define MAX_LIVING_PARTICLES 100


/*An object of this class will emit particles.*/
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

        //the texture of emited particles.
        void setTexture(TextureLocation texture);
        //position of the texture of the emited particles (same as for image)
        void setTexturePosition(vec2f texturePosition);
        //size of the texture of the emited particles (same as for image)
        void setTextureSize(vec2f textureSize);
        //color multiplier of the particles
        void setColor(vec4f color);
        //layer in which particles will be emited
        void setLayer(int layer);

        //position of the emitter
        inline void setPosition(vec2f& position){
            this->position = position;
        }
        inline void setPosition(vec2f&& position){
            this->position = position;
        }

        //velocity of the emitter
        inline void setVelocity(vec2f velocity){
            this->velocity = velocity;
        }
        
        //range of positions around the emiter in which particles can spawn
        inline void setPositionRange(vec2f lowerLimit, vec2f higherLimit){
            lowPositionLimit = lowerLimit;
            highPositionLimit = higherLimit;
        }

        //range of possible particle initial velocities
        inline void setVelocityRange(vec2f lowerLimit, vec2f higherLimit){
            lowVelocityLimit = lowerLimit;
            highVelocityLimit = higherLimit;
        }

        //size limits for the particles. X and Y sizes can be picked independently or can be ratio-locked.
        inline void setSizeRange(vec2f lowerLimit, vec2f higherLimit, bool keepRatio){
            keepSizeRatio = keepRatio;
            lowSizeLimit = lowerLimit;
            highSizeLimit = higherLimit;
        }

        //size multiplier of the particles as they are updated.
        void setScalingFactor(float scalingFactor);

        //range of possible lifetimes for particles.
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

        //emit a single particle
        void emit();

        //emit multiple particles
        void emit(int repeat);
};