#include "sound/soundSource.h"
#include "sound/soundManager.h"

SoundSource::SoundSource(){
    soundSourceName = 0;
    alGenSources(1, &soundSourceName);
}

SoundSource::~SoundSource(){
    if(soundSourceName)
        alDeleteSources(1, &soundSourceName);
}

void SoundSource::queueSound(SoundLocation soundIndex){
    SoundManager::queueBuffer(soundSourceName, soundIndex);
}

void SoundSource::attachSound(SoundLocation soundIndex){
    int state;
    alGetSourcei(soundSourceName, AL_SOURCE_STATE, &state);
    if(state == AL_STOPPED || state == AL_INITIAL)
        SoundManager::attachBuffer(soundSourceName, soundIndex);
}

void SoundSource::play(){
    alSourcePlay(soundSourceName);
}

void SoundSource::pause(){
    alSourcePause(soundSourceName);
}

void SoundSource::stop(){
    alSourceStop(soundSourceName);
}

void SoundSource::clear(){
    stop();
    alSourcei(soundSourceName, AL_BUFFER, 0);
    int queBuffers;
    alGetSourcei(soundSourceName, AL_BUFFERS_QUEUED, &queBuffers);
    if(!queBuffers)
        return;

    unsigned int* deletedBuffers = new unsigned int[queBuffers];
    alSourceUnqueueBuffers(soundSourceName, queBuffers, deletedBuffers);

    delete[] deletedBuffers;
}

void SoundSource::setPosition(const vec2f& pos){
    alSource3f(soundSourceName, AL_POSITION, pos.x, pos.y, 0);
}
void SoundSource::setVelocity(const vec2f& vel){
    alSource3f(soundSourceName, AL_VELOCITY, vel.x, vel.y, 0);
}
void SoundSource::setLooping(bool looping){
    alSourcei(soundSourceName, AL_LOOPING, looping);
}

//distance at which set gain is measured
void SoundSource::setReferenceDistance(float distance){
    alSourcef(soundSourceName, AL_REFERENCE_DISTANCE, distance);
}
