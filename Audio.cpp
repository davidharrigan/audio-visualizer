#include "Audio.h"
#include <string>
#include <stdio.h>
#include <math.h>

static FMOD_CHANNELGROUP *channelGroup;
static FMOD_SYSTEM *system;

float fftValues_[8192];			//
float fftInterpValues_[8192];			//
float fftSpectrum_[8192];		// maximum #ofFmodSoundPlayer is 8192, in fmodex....

// Global functions
//----------------------------------------------------------- 

int ofNextPow2(int x) {
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

//
// Code borrowed from openFrameworks sounds library. 
//
float *getSoundSpectrum(int nBands){

	// 	set to 0
	for (int i = 0; i < 8192; i++){
		fftInterpValues_[i] = 0;
	}

	// 	check what the user wants vs. what we can do:
	if (nBands > 8192){
		nBands = 8192;
	} else if (nBands <= 0){
		nBands = 1;
		return fftInterpValues_;
	}

	// 	FMOD needs pow2
	int nBandsToGet = ofNextPow2(nBands);
	if (nBandsToGet < 64) nBandsToGet = 64;  // can't seem to get fft of 32, etc from fmodex

	// 	get the fft
	FMOD_System_GetSpectrum(system, fftSpectrum_, nBandsToGet, 0, FMOD_DSP_FFT_WINDOW_HANNING);

	// 	convert to db scale
	for(int i = 0; i < nBandsToGet; i++){
        fftValues_[i] = 10.0f * (float)log10(1 + fftSpectrum_[i]) * 2.0f;
	}

	// 	try to put all of the values (nBandsToGet) into (nBands)
	//  in a way which is accurate and preserves the data:
	//

	if (nBandsToGet == nBands){

		for(int i = 0; i < nBandsToGet; i++){
			fftInterpValues_[i] = fftValues_[i];
		}

	} else {

		float step 		= (float)nBandsToGet / (float)nBands;
		//float pos 		= 0;
		// so for example, if nBands = 33, nBandsToGet = 64, step = 1.93f;
		int currentBand = 0;

		for(int i = 0; i < nBandsToGet; i++){

			// if I am current band = 0, I care about (0+1) * step, my end pos
			// if i > endPos, then split i with me and my neighbor

			if (i >= ((currentBand+1)*step)){

				// do some fractional thing here...
				float fraction = ((currentBand+1)*step) - (i-1);
				float one_m_fraction = 1 - fraction;
				fftInterpValues_[currentBand] += fraction * fftValues_[i];
				currentBand++;
				// safety check:
				if (currentBand >= nBands){
                    printf("currentBand is bigger");
				}

				fftInterpValues_[currentBand] += one_m_fraction * fftValues_[i];

			} else {
				// do normal things
				fftInterpValues_[currentBand] += fftValues_[i];
			}
		}

		// because we added "step" amount per band, divide to get the mean:
		for (int i = 0; i < nBands; i++){
			fftInterpValues_[i] /= step;
			if (fftInterpValues_[i] > 1)fftInterpValues_[i] = 1; 	// this seems "wrong"
		}

	}

	return fftInterpValues_;
}

// Constructor
//-------------------------------------------
Audio::Audio() {
    pan = 0;
    volume = 1.0;
    sampleRate = 44100;
}

// Destructor
//-------------------------------------------
Audio::~Audio() {
}

//
// Initialize FMOD system
//
void Audio::initialize() {
    FMOD_System_Create(&system);
    FMOD_System_SetOutput(system, FMOD_OUTPUTTYPE_ALSA);
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    FMOD_System_GetMasterChannelGroup(system, &channelGroup);
}

//
// Close FMOD system
//
void Audio::close() {
    FMOD_System_Close(system);
}

//
//
//
bool Audio::loadFile(std::string fileName) {
    result = FMOD_System_CreateSound(system, fileName.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);

    if (result != FMOD_OK) {
        printf("Error loading %s\n", fileName.c_str());
        return false;
    }
    FMOD_Sound_GetLength(sound, &length, FMOD_TIMEUNIT_PCM);
    return true;
}

//
//
//
void Audio::play() {
   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
   //FMOD_Channel_GetFrequency(channel, &sampleRate);
   FMOD_Channel_SetVolume(channel, 1);
   FMOD_Channel_SetPan(channel, pan);
   FMOD_Channel_SetFrequency(channel, sampleRate);
   FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
   FMOD_System_Update(system);
    
}

/*
int main(int argc, char *argv[]) {
    Audio *a = new Audio();
    a->initialize();
    a->loadFile("sonic.wav");
    for(;;)
        a->play();
    a->close();
}
*/
