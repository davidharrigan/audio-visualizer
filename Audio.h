/*
 * Audio.h - encapsulates all audio activities in the program
 *
 * David Harrigan
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "./fmod/inc/fmod.hpp"
#include "./fmod/inc/fmod_errors.h"
#include <string>

#define SAMPLE_RATE 44100
#define VOLUME 1
#define SPEED 1


// Global functions
float *getSoundSpectrum(int);

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
    FMOD::Channel *channel;
    FMOD::Sound *sound;
    //FMOD_STREAM *stream;
};

#endif
