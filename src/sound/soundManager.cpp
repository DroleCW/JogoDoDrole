#include "sound/soundManager.h"
#include "sound/sound.h"

char* SoundManager::soundPaths[NUMBER_OF_SOUNDS] = {};
Sound* SoundManager::loadedSounds[NUMBER_OF_SOUNDS] = {};
ALCdevice* SoundManager::selectedDevice = nullptr;
ALCcontext* SoundManager::currentContext = nullptr;

void SoundManager::init(){

    loadSoundPaths(SOUND_INDEX_FILE);

    for(int i = 0; i < NUMBER_OF_SOUNDS; i++)
        loadedSounds[i] = nullptr;

    selectedDevice = alcOpenDevice(nullptr);
    currentContext = alcCreateContext(selectedDevice, nullptr);
    alcMakeContextCurrent(currentContext);
}

void SoundManager::terminate(){

    for(int i = 1; i < NUMBER_OF_SOUNDS; i++)
        delete[] soundPaths[i];

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(currentContext);
    alcCloseDevice(selectedDevice); 

}


bool SoundManager::loadSound(SoundLocation soundIndex){
     if(loadedSounds[soundIndex] == nullptr){
        Sound* newSound = new Sound();
        if(newSound->loadFromFile(soundPaths[soundIndex])){
            loadedSounds[soundIndex] = newSound;
            //totalLoadedSounds++;
            return true;
        }
        else{
            delete newSound;
            return false;
        }
    } 

    return true;
}

void SoundManager::unloadSound(SoundLocation soundIndex){
    if(loadedSounds[soundIndex]){
        delete loadedSounds[soundIndex];
        loadedSounds[soundIndex] = nullptr;
        //totalLoadedSounds--;
    } 
}

bool SoundManager::loadSoundPaths(const char* indicesFilePath){

    std::ifstream soundIndicesFile;

    soundIndicesFile.open(indicesFilePath);

    for(int i = 1; i < NUMBER_OF_SOUNDS; i++)
        soundPaths[i] = new char[MAX_SOUND_PATH_SIZE];


    if(soundIndicesFile.is_open()){
        int index = 1;
        while (soundIndicesFile.peek() != EOF && index < NUMBER_OF_SOUNDS){
            soundIndicesFile.ignore(5, ' ');
            soundIndicesFile.getline(soundPaths[index], 40);
            index++;
        }
        if(index == NUMBER_OF_SOUNDS)
            return true;
        else{
            printf("ERROR: Failure to load all sound files\n");
            return false; 
        }
    }
    else{
        printf("ERROR: Could not load sound paths.\n");
        return false;
    }
}

void SoundManager::queueBuffer(unsigned int soundSourceName, SoundLocation soundIndex){
    alSourceQueueBuffers(soundSourceName, 1, loadedSounds[soundIndex]->getBufferName());
}

void SoundManager::attachBuffer(unsigned int soundSourceName, SoundLocation soundIndex){
    alSourcei(soundSourceName, AL_BUFFER, *loadedSounds[soundIndex]->getBufferName());
}


