/**
 * Scene.cpp - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */

#include "Scene.h"

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
    //glScalef(0.5, 0.5, 2.0);
    std::vector<Object3D*>::iterator it;
    int i;
   // float* buffer;
    float* samples = getSoundSpectrum(100);
    float ampAvg = 0;
    //float* samples = getSpectrum();
    //PowerSpectrum(256, bufferIn, buffer);
    for (i=0, it = objects.begin(); it != objects.end(); i++, it++) {
        float freq = samples[i];
        freq *= 0.96; // make fft smoother
        if (freq < samples[i]) 
            freq = samples[i];
        ampAvg += freq;
        (*it)->redraw(freq);
    }
    ampAvg /= i;
    //float hzRange = (44100 / 2) / *samples;
    glClearColor(0.1,0.5, ampAvg*1.5, 1);
    //delete samples;
    //glClearColor(0.5, 0.5, getAvgAmp()*0.6, 0.5);
    
}

