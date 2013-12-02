#include "Audio.h"
#include <string.h>
#include <string>

extern Packet *sharedBuffer;
SF_Container sf;
bool finished;
float sample;
int order = 0;

//
// Callback function for PortAudio during audio streaming
//
static int paCallback(const void *inputBuffer, 
                      void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags, 
                      void *userData) {
    
    int i, j, bufferIndex;
    float *out = (float*) outputBuffer;
    float fileBuffer[framesPerBuffer*PAC_CHANNELS];

    //search through the shared buffer for free packet
    for (i=0, bufferIndex=0; i<BUFFER_SIZE; i++, bufferIndex++) {
        //if free packet found, break loop
        if (sharedBuffer[i].free) break;
        //if we're on the last packet and none are free, return
        else if (i>=BUFFER_SIZE) return paContinue; 
    }

    //set and increment order
    sharedBuffer[bufferIndex].order = order;
    order += 1;
    
    //get samples from sound file
    int readcount = framesPerBuffer;
    if (!inputBuffer)
        readcount = sf_readf_float(sf.file, fileBuffer, framesPerBuffer);

    //fill buffer from sound file
    for (i=0; i<framesPerBuffer; i++) {
        for (j=0; j<PAC_CHANNELS; j++) {
            //send sample to output buffer
            sample = fileBuffer[STEREO*i + j];
            out[STEREO*i + j] = sample;

            //save information in the shared buffer
            sharedBuffer[bufferIndex].averageAmp += sample;
            sharedBuffer[bufferIndex].frames[i][j] = sample;
        }
    }
    sharedBuffer[bufferIndex].averageAmp /= (float)framesPerBuffer;
    sharedBuffer[bufferIndex].free = false;

    //if we've reached the end of the file, end callback
    if ((unsigned)readcount < framesPerBuffer) {
        finished = true;
        return paComplete;
    }
    return paContinue;
}

//
// Returns PortAudio output device parameters
//
PaStreamParameters getStreamParams() {
    PaStreamParameters params;
    params.device = Pa_GetDefaultOutputDevice();
    params.channelCount = OUT_CHANNELS;
    params.sampleFormat = paFloat32;
    params.suggestedLatency = Pa_GetDeviceInfo(params.device)->defaultLowOutputLatency;
    params.hostApiSpecificStreamInfo = NULL;
    return params;
}

//
// Open and read audio file. Initialize and start PortAudio stream
//
bool startAudio(PaStream *stream, const char* filename) {

    //Open file
    if ((sf.file = sf_open(filename, SFM_READ, &sf.info)) == NULL) {
        printf("Error reading file");
        return false;
    }
    PaError err = Pa_Initialize();
    int samplerate = sf.info.samplerate;
    
    //port audio initialize
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        return false;
    }
    PaStreamParameters outputParams = getStreamParams();

    //open the stream
    err = Pa_OpenStream(
            &stream,
            0,
            &outputParams, 
            samplerate, 
            BUFFER,
            paNoFlag,
            paCallback,
            NULL);
    if (err != paNoError) {
        printf("PortAudio error while opening stream: %s\n", Pa_GetErrorText(err));
        return false;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        printf("PortAudio error while starting stream: %s\n", Pa_GetErrorText(err));
        return false;
    }
    return true;
}

//
// End audio stream
//
void endAudio(PaStream *stream) {
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    sf_close(sf.file);
}

float getSample() {
    return sample;
}

int getOrderCount() {
    return order;
}
/*
//
// Simple main to test audio playback
//
int main(int argc, char *argv[]) {
    PaStream *stream;
    SF_Container infile; 
    finished = false; 

    if (argc != 2) {
        printf("No sound file\n");
        return EXIT_FAILURE; 
    }

    startAudio(&stream, argv[1]);
    while (!finished);
    endAudio(&stream);
    return EXIT_SUCCESS;
}
*/
