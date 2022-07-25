#include "sound/sound.h"
#include "sound/soundManager.h"

Sound::Sound(){
    bufferName = 0;
}

Sound::~Sound(){
    if(bufferName)
        alDeleteBuffers(1, &bufferName);
}

bool Sound::loadFromFile(const char* path){
    SF_INFO info;
    SNDFILE* file = sf_open(path, SFM_READ, &info);

    freq = info.samplerate;
    channels = info.channels;
    uint8_t* data;
    alGenBuffers(1, &bufferName);

    if((info.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_S8){
        bits = 8;
        size = info.frames*channels*(bits/8);
        data = new uint8_t[size];
        sf_read_short(file, (short*)data, size);
        if(channels == 1)
            alBufferData(bufferName, AL_FORMAT_MONO8, data, size, freq);
        else if(channels == 2)
            alBufferData(bufferName, AL_FORMAT_STEREO8, data, size, freq);
    }
    else if((info.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_16){
        
        bits = 16;
        size = info.frames*channels*(bits/8);
        data = new uint8_t[size];
        sf_read_short(file, (short*)data, size/2);
        if(channels == 1)
            alBufferData(bufferName, AL_FORMAT_MONO16, data, size, freq);
        else if(channels == 2)
            alBufferData(bufferName, AL_FORMAT_STEREO16, data, size, freq);
    }

    delete[] data;
    sf_close(file);
    return true;
}