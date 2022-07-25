#pragma once
#include "sound/sndfile.h"

//A sound effect or music
class Sound{

    private:
        unsigned int bufferName;
        unsigned int freq, bits, channels, size;

    public:
        Sound();
        ~Sound();

        bool loadFromFile(const char* path);

        inline unsigned int* getBufferName(){
            return &bufferName;
        }
};