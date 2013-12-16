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
#include <vector>

#define SAMPLE_RATE 48000;
#define VOLUME 1
#define SPEED 1

// Global functions
float *getSoundSpectrum(int);
void getSoundSpectrum(int, float*);

class Audio {

public:
    Audio();
    ~Audio();
    void initialize();
    void close();

    bool loadFile();
    void saveFile(std::string fileName);
    void play();
    void stop();
    void next();
    
    unsigned int curFile;
    float pan;
    float sampleRate;
    float volume;
    unsigned int length;

    std::vector<std::string> files;

    FMOD_RESULT result;
    FMOD::Channel *channel;
    FMOD::Sound *sound;
};

#endif
