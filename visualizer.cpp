#include <iostream>
#include <cstdlib>

//STK
#include "RtAudio.h"

const char *filename = NULL;

bool initAudio();

int main (int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Need a audio file" << std::endl;
        return -1;
    }
    filename = argv[1];
    initAudio(); 
}

bool initAudio() {
    RtAudio dac;
    if (dac.getDeviceCount() < 1) {
        std::cout << "No audio device found" << std::endl;
    }
}
