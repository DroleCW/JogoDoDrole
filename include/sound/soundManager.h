#pragma once

#include "sound/soundSource.h"
#include "sound/sound.h"
#include "sound/AL/al.h"
#include "sound/AL/alc.h"
#include "sound/soundLocations.h"
#include <fstream>

class Sound;

//handles sound loading, unloading and parameters.
class SoundManager{
    private:
        static char* soundPaths[NUMBER_OF_SOUNDS];//vector of sound file paths
        static Sound* loadedSounds[NUMBER_OF_SOUNDS];//vector of all possible loaded sounds
        static ALCdevice* selectedDevice;
        static ALCcontext* currentContext;

    public:
        static void init();
        //all sound related objects should be destroyed before calling this.
        static void terminate();

        static bool loadSound(SoundLocation soundIndex);
        static void unloadSound(SoundLocation soundIndex);
        
        //loads the paths of the sound files. Sound to SoundLocation association happens here.
        static bool loadSoundPaths(const char* indicesFilePath);

        //used by the soundSource objects-------
        static void queueBuffer(unsigned int soundSourceName, SoundLocation soundIndex);
        static void attachBuffer(unsigned int soundSourceName, SoundLocation soundIndex);
        //--------------------------------------

        /*where the sound receptor is in the world. The library works with 3D sound, which is here decomposed
        in a 2D position with a depth value.*/
        inline static void setListenerPosition(const vec2f& pos, float depth){
            alListener3f(AL_POSITION, pos.x, pos.y, depth);
        }

        /*The listener velocity in the world. It will not update the listener position, only used
        to simulate doppler effects*/
        inline static void setListenerVelocity(const vec2f& vel){
            alListener3f(AL_VELOCITY, vel.x, vel.y, 0);
        }


    private:

        SoundManager(){

        }
        ~SoundManager(){

        }

};