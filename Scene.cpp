/**
 * Scene.cpp - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */

#include "Scene.h"

#include <fmodex/fmod.h>
#include <iostream>
#include <GL/glui.h>
#include "Audio.h"

//Packet *sharedBuffer;
int bufferIndex;

// Constructors
// ------------------------------------------------------------------

Scene::Scene() {
    bufferIndex = 0;
}


// Public Methods
// ------------------------------------------------------------------

//
// adds an object to the vector
//
void Scene::addObject(Object3D *newObject) {
    objects.push_back(newObject);
}

void Scene::addObject2(Object3D *newObject) {
    objects2.push_back(newObject);
}

//
// clears the object vector
//
void Scene::clear() {
    objects.clear();
    redraw();
}

//
// Redraws the scene
//
void Scene::redraw() {
    glTranslatef(0, -1, 0.0);
    std::vector<Object3D*>::reverse_iterator it;
    std::vector<Object3D*>::iterator it2;
    int i;
    float ampAvg = 0;
    //2028, 4096, and 8192 are good
    int sampleSize = 4096;
    float* samples = getSoundSpectrum(sampleSize);
    //float* samples = getSpectrum();
    int steps = sampleSize / 12 / 100;
    //printf("steps: %d", steps);
    //int steps = 1; 
    for (i=10, it = objects.rbegin(); it != objects.rend(); i+=steps, it++) {
        float freq = 0;
        for (int j=0; j<steps; j++) {
            freq += samples[i + j];
        }
        ampAvg += freq;
        freq /= steps;
        /*freq *= 0.9; // make fft smoother
        if (freq < samples[i]) 
            freq = samples[i];*/
        (*it)->redraw(freq);
    }

    ampAvg /= i;
    glTranslatef(0,-0.005,0);
    glRotatef(90,1,0,0);
    //glTranslatef(0.01,0,0.01);
    for (it=objects2.rbegin(); it != objects2.rend(); i+=steps, it++) {
        float freq = 0;
        for (int j=0; j<steps; j++) {
            freq += samples[i + j];
        }
    //dd    ampAvg += freq;
        freq /= steps;
        /*freq *= 0.9; // make fft smoother
        if (freq < samples[i]) 
            freq = samples[i];*/
        (*it)->redraw(freq);

    }
    //float hzRange = (44100 / 2) / *samples;
    glClearColor(0.1,0.5, ampAvg*1.6, 1);
    //delete samples;
    //glClearColor(0.5, 0.5, getAvgAmp()*0.6, 0.5);
}

