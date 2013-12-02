#ifndef AUDIO_H_
#define AUDIO_H_

#include <sndfile.h>
#include <portaudio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#define OUT_CHANNELS 2
#define SAMPLE_RATE 48000
#define BUFFER 256
#define STEREO 2

#define BUFFER_SIZE 100
#define PAC_CHANNELS 2

#define PI 3.1415926535

typedef struct {
    float frames[BUFFER][PAC_CHANNELS];
    bool free;
    int order;
    float averageAmp;
} Packet;

typedef struct {
    SNDFILE *file;
    SF_INFO info;
} SF_Container;

PaStreamParameters getStreamParams();
bool startAudio(PaStream*, const char*);
void endAudio(PaStream*);
float getSample();
int getOrderCount();
#endif 
