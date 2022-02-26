#pragma once

#include "sound/soundSource.h"
#include "sound/sound.h"
#include "sound/AL/al.h"
#include "sound/AL/alc.h"
#include "sound/soundLocations.h"
#include <fstream>

class Sound;

class SoundManager{
    private:
        static char* soundPaths[NUMBER_OF_SOUNDS];
        static Sound* loadedSounds[NUMBER_OF_SOUNDS];
        static ALCdevice* selectedDevice;
        static ALCcontext* currentContext;

    public:
        static void init();
        static void terminate();

        static bool loadSound(SoundLocation soundIndex);
        static void unloadSound(SoundLocation soundIndex);
        
        static bool loadSoundPaths(const char* indicesFilePath);

        static void queueBuffer(unsigned int soundSourceName, SoundLocation soundIndex);
        static void attachBuffer(unsigned int soundSourceName, SoundLocation soundIndex);


    private:

        SoundManager(){

        }
        ~SoundManager(){

        }

};