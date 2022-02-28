#pragma once
#include "sound/soundLocations.h"
#include "math/vec2f.h"

class SoundSource{
    private:
        unsigned int soundSourceName;


    public:
        SoundSource();
        ~SoundSource();

        void queueSound(SoundLocation soundIndex);
        void attachSound(SoundLocation soundIndex);
        void play();
        void pause();
        void stop();
        void clear();

        void setPosition(const vec2f& pos);
        void setVelocity(const vec2f& vel);
        void setLooping(bool looping);
        void setReferenceDistance(float distance);
};