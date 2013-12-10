
#include "Audio.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <algorithm>

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
	sys->getSpectrum(fftSpectrum_, nBandsToGet, 0, FMOD_DSP_FFT_WINDOW_HANNING);

/*
    //TRASH
    specLeft = new float[nBandsToGet];
    specRight = new float[nBandsToGet];
	FMOD_System_GetSpectrum(sys, specLeft, nBandsToGet, 0, FMOD_DSP_FFT_WINDOW_HANNING);
	FMOD_System_GetSpectrum(sys, specRight, nBandsToGet, 1, FMOD_DSP_FFT_WINDOW_HANNING);

    // Average volume
    for (int i=0; i<nBandsToGet; i++) 
        fftValues_[i] = (specLeft[i] + specRight[i]) / 2;

    delete specLeft;
    delete specRight;
    //ENDTRASH
    */

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
    /*
    //Find max volume
    auto maxIterator = std::max_element(
            &fftInterpValues_[0], 
            &fftInterpValues_[nBands]);
    float maxVol = *maxIterator;

    //Normalize
    if (maxVol !=0)
        std::transform(&fftInterpValues_[0], 
                       &fftInterpValues_[nBands], 
                       &fftInterpValues_[0], 
                       [maxVol] (float dB)->float {return dB / maxVol;});

    */
	return fftInterpValues_;
}

float* getSpectrum() {
    int sampleSize = 1024;
    /*
    float *specLeft, *specRight;
    specLeft = new float[sampleSize];
    specRight = new float[sampleSize];
    float *spec = new float[sampleSize];
	FMOD_System_GetSpectrum(sys, specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
	FMOD_System_GetSpectrum(sys, specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);
    // Average volume
    for (int i=0; i<sampleSize; i++) 
        spec[i] = (specLeft[i] + specRight[i]) / 2;
    

    delete specLeft;
    delete specRight;
    */
    //FMOD_System_GetSpectrum(sys, fftInterpValues_, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
    return fftInterpValues_;
}

// Constructor
//-------------------------------------------
Audio::Audio() {
    FMOD::DSP *dsp;
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
    result = System_Create(&sys);
    //sys->setOutput(FMOD_OUTPUTTYPE_ALSA);
    sys->init(32, FMOD_INIT_NORMAL, NULL);
    sys->getMasterChannelGroup(&channelGroup);
}

//
// Close FMOD system
//
void Audio::close() {
    result = sys->close();
}

//
// load audio file
//
bool Audio::loadFile(std::string fileName) {
    result = sys->createSound( fileName.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);

    if (result != FMOD_OK) {
        printf("Error loading %s\n", fileName.c_str());
        printf("(%d) %s\n", result, FMOD_ErrorString(result));
        return false;
    }
    sound->getLength(&length, FMOD_TIMEUNIT_PCM);
    return true;
}

//
//
//
void Audio::play() {
   sys->playSound( FMOD_CHANNEL_FREE, sound, 0, &channel);
   //FMOD_Channel_GetFrequency(channel, &sampleRate);
   channel->setVolume(1);
   channel->setPan(pan);
   channel->setFrequency(sampleRate);
   channel->setMode(FMOD_LOOP_OFF);
   sys->update();
    
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
