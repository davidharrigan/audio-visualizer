#include "Audio.h"
#include <string.h>
#include <string>

Packet *sharedBuffer;
SF_Container sf;
bool finished;

//
//
//
static int paCallback(const void *inputBuffer, 
                      void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags, 
                      void *userData) {
    
    int i, j, bufferIndex;
    float sample; 
    float *out = (float*) outputBuffer;
    float *in  = (float*) inputBuffer;
    float fileBuffer[framesPerBuffer*PAC_CHANNELS];
    static int order = 0;
    
    /*
    //search through the shared buffer for free packet
    for (i=0, bufferIndex=0; i<BUFFER_SIZE; i++, bufferIndex++) {
        // break if free packet is found
        if (sharedBuffer[i].free) 
            break;
        
        // if on last packet and none are free, return
        if (i>=BUFFER_SIZE)
            return paContinue;
    }
    
    //set and increment order
    sharedBuffer[bufferIndex].order = order;
    order++;
    */
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
            /*
            //window and send sample to shared buffer
            sharedBuffer[bufferIndex].averageAmp += (float)sample;
            //Do more here later when OpenGL is ready
            sharedBuffer[bufferIndex].frames[i][j] = sample;
            */
        }
    }
    /*
    sharedBuffer[bufferIndex].averageAmp /= (float)framesPerBuffer;
    sharedBuffer[bufferIndex].free = false;
    */
    //if we've reached the end of the file, end callback
    if (readcount < framesPerBuffer) {
        finished = true;
        return paComplete;
    }
    return paContinue;
}

//
//
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
//
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
//
//
void endAudio(PaStream *stream) {
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    sf_close(sf.file);
}

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
    return 0;
}
