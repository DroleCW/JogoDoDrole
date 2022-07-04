#include "graphics/particles/particle.h"

Particle::Particle(TextureLocation textureIndex):Image(textureIndex, false), velocity(0.0f, 0.0f), lifetime(0), isAlive(false),
scalingFactor(1.0f){

}

Particle::~Particle(){

}

bool Particle::update(float dt){
    move(velocity*dt);
    scale(scalingFactor);

    lifetime -= dt;
    isAlive = lifetime > 0;
    
    return isAlive;    
}