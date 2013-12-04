#ifndef AUDIO_H_
#define AUDIO_H_

#include <fmodex/fmod.h>
#include <fmodex/fmod_errors.h>
#include <string>

#define SAMPLE_RATE 44100
#define VOLUME 1
#define SPEED 1

// Global static variables
static FMOD_CHANNELGROUP *channelGroup;
static FMOD_SYSTEM *sys;

// Global functions
float *getSoundSpectrum(int);
float *getSpectrum();

class Audio {

public:
    Audio();
    ~Audio();
    void initialize();
    void close();

    bool loadFile(std::string fileName);
    void play();
    
    float pan;
    float sampleRate;
    float volume;
    unsigned int length;


    FMOD_RESULT result;
    FMOD_CHANNEL *channel;
    FMOD_SOUND *sound;
    //FMOD_STREAM *stream;
};

#endif
