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
#include "Box.h"

//Packet *sharedBuffer;
int bufferIndex;

// Constructors
// ------------------------------------------------------------------

Scene::Scene() {
    sampleSize = 4096; //2028, 4096, and 8192 are good
    steps = 3;
    numBars = 100;
    float size = 2.0 / numBars;
    for (int i=0; i<numBars; i++) {
        Box *b = new Box();
        b->setSize(size, 0, size);
        b->setColor(new Color(0,0,0));
        b->setLocation(1-i*size, 0, 0);
        objects.push_back(b);
    }
    numBars = 200;
    size = 2.0 / numBars;
    for (int i=0; i<numBars; i++) {
        Box *b = new Box();
        b->setSize(size, 0, size);
        b->setColor(new Color(0,0,0));
        b->setLocation(1-i*size, 0, 0);
        objects2.push_back(b);
    }
}


// Public Methods
// ------------------------------------------------------------------

//
// Redraws the scene
//
void Scene::redraw() {
    glTranslatef(0, -1, 0);
    int i;
    float ampAvg = 0;
    float* samples = getSoundSpectrum(sampleSize);

    for (i=10, it = objects.rbegin(); it != objects.rend(); i+=steps, it++) {
        float freq = 0;
        for (int j=0; j<steps; j++) {
            freq += samples[i + j];
            ampAvg += freq;
        }
        freq /= steps;
        (*it)->redraw(freq);
    }
    ampAvg /= i;
    glTranslatef(0,-0.005,0);
    glRotatef(90,1,0,0);
   
    for (it=objects2.rbegin(); it != objects2.rend(); i+= steps, it++) {
        float freq = 0;
        for (int j=0; j<steps; j++) 
            freq += samples[i + j];

        freq /= steps; 
        (*it)->redraw(freq);
    }
    glClearColor(0,0, ampAvg*0.2, 1.0);
}
