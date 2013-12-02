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

Packet *sharedBuffer;
int bufferIndex;

// Constructors
// ------------------------------------------------------------------

Scene::Scene() {
    fftObject = new fft();
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
    //glTranslatef(0.5, 0.5, 0.0);
    //glScalef(0.5, 0.5, 2.0);
    std::vector<Object3D*>::iterator it;
    int i;
    float* buffer = getBuffer();
    for (i=0, it = objects.begin(); it != objects.end(); i++, it++) {
        float freq = buffer[i+50];
        freq *= 0.96;
        if (freq < buffer[i+40]) 
            freq = buffer[i+40];
          (*it)->redraw(freq);
    }
}

