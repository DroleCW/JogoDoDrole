#include "graphics/particles/particleSystem.h"
#include <stdlib.h>
#include <time.h>
#include <graphics/graphicManager.h>

#define RAND_0TO1_F ((rand()%4096)/4096.0f)

ParticleSystem::ParticleSystem():position({0.0f, 0.0f}), velocity({0.0f, 0.0f}),
texture(NO_TEXTURE_LOCATION),
lowPositionLimit(0, 0), highPositionLimit(0, 0),
lowVelocityLimit(0, 0), highVelocityLimit(0, 0),
lowLifetime(0), highLifetime(1),
insertionIt(0), it(0),
livingParticles(0){
    srand(time(nullptr));
    particles = new Particle[MAX_LIVING_PARTICLES];
    GraphicManager::addParticleSystem(this);

}

ParticleSystem::~ParticleSystem(){
    delete[] particles;
    GraphicManager::removeParticleSystem(this);
}

void ParticleSystem::update(float dt){
    for(int j = insertionIt-1, count = 0; j != insertionIt && count < livingParticles; j--){
        if(j < 0)
            j = MAX_LIVING_PARTICLES-1;
        if(particles[j].getIsAlive()){
            if(!particles[j].update(dt))
                livingParticles--;
            count++;
        }
    }
}

void ParticleSystem::setTexture(TextureLocation texture){
    this->texture = texture;
    
    for(int j = 0; j < MAX_LIVING_PARTICLES; j++)
        particles[j].setTexture(texture);
}
void ParticleSystem::setTexturePosition(vec2f texturePosition){
    for(int j = 0; j < MAX_LIVING_PARTICLES; j++)
        particles[j].setTexturePosition(texturePosition);
}

void ParticleSystem::setTextureSize(vec2f textureSize){
    for(int j = 0; j < MAX_LIVING_PARTICLES; j++){
        particles[j].setTextureSize(textureSize);
        particles[j].setSize({100.0f, 100.0f});
    }
    
}

void ParticleSystem::setParticleSize(vec2f size){
    for(int j = 0; j < MAX_LIVING_PARTICLES; j++){
        particles[j].setSize(size);
    }
}

void ParticleSystem::setLayer(int layer){
    for(int j = 0; j < MAX_LIVING_PARTICLES; j++){
        particles[j].setLayer(layer);
    }
}

void ParticleSystem::emit(){
    if(livingParticles == MAX_LIVING_PARTICLES)
        return;

    while(particles[insertionIt].getIsAlive()){//find a dead particle slot
        insertionIt++;
        if(insertionIt >= MAX_LIVING_PARTICLES)
            insertionIt = 0;
    }

    vec2f newPosition(RAND_0TO1_F*(highPositionLimit.x-lowPositionLimit.x) + lowPositionLimit.x, RAND_0TO1_F*(highPositionLimit.y-lowPositionLimit.y) + lowPositionLimit.y);
    newPosition += position;
    particles[insertionIt].setPosition(newPosition);
    particles[insertionIt].setVelocity({RAND_0TO1_F*(highVelocityLimit.x-lowVelocityLimit.x) + lowVelocityLimit.x, RAND_0TO1_F*(highVelocityLimit.y-lowVelocityLimit.y) + lowVelocityLimit.y});
    particles[insertionIt].setLifetime(RAND_0TO1_F*(highLifetime - lowLifetime) + lowLifetime);

    livingParticles++;
}

void ParticleSystem::emit(int repeat){
    if(livingParticles == MAX_LIVING_PARTICLES)
        return;
    while(repeat){
        emit();
        repeat--;
    }
}

Particle* ParticleSystem::getNextLivingParticle(){

    if(it >= MAX_LIVING_PARTICLES)
            return nullptr;
    while(!particles[it].getIsAlive()){
        it++;
        if(it >= MAX_LIVING_PARTICLES){
            return nullptr;
        }
    }
    return &particles[it++];
}