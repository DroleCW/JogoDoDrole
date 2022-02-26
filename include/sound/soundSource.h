#pragma once
#include "sound/soundLocations.h"

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
};