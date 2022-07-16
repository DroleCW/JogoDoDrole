#pragma once
#include "sound/soundLocations.h"
#include "math/vec2f.h"

//A sound emitter.
class SoundSource{
    private:
        unsigned int soundSourceName;


    public:
        SoundSource();
        ~SoundSource();

        //creates a queue of sound to be played.
        void queueSound(SoundLocation soundIndex);

        //attaches a sound to the source that will always be played when play() is called.
        void attachSound(SoundLocation soundIndex);
        void play();
        void pause();
        void stop();
        void clear();

        void setPosition(const vec2f& pos);
        void setVelocity(const vec2f& vel);
        void setLooping(bool looping);

        //Distance at which set gain is measured
        void setReferenceDistance(float distance);
};