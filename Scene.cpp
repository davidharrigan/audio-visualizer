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
    curLine = 0;
    sampleSize = 1600; //2028, 4096, and 8192 are good
    steps = 4;
    numBars = 22;
    float size = 2.0 / (numBars*6);
    for (int i=0; i<numBars*2; i++) {
        std::vector<Object3D*>* temp = new std::vector<Object3D*>();
        for (int j=0; j<numBars; j++) {
            Box *b = new Box();
            b->setSize(size, 0, size);
            b->setColor(new Color(1,1,1));
            b->setLocation(1-j*size*6, 0, 1-i*size);
            temp->push_back(b); 
        }
        lines.push_back(temp);
    }
}


// Public Methods
// ------------------------------------------------------------------

//
// Redraws the scene
//
void Scene::redraw() {
    if (curLine >= lines.size())
        curLine = 0;
    glTranslatef(0, 0, 1);
    std::vector<Object3D*> objects = *lines[curLine];
    std::vector<Object3D*>::reverse_iterator it;
    std::vector<std::vector<Object3D*>* >::iterator itt;
    int i;
    float ampAvg = 0;
    float* samples = getSoundSpectrum(sampleSize);
    //float* samples = getSpectrum();

    // move up all lines
    for (i=0, itt=lines.begin(); itt != lines.end(); itt++, i++) {
        for (it=(*itt)->rbegin(); i==curLine, it!=(*itt)->rend(); it++) {
            (*it)->moveUp();
            (*it)->redraw(-1);
        }
    }
    
    for (i=0, it = objects.rbegin(); it != objects.rend(); i+=steps, it++) {
        float freq = 0;
        float highest = -1;
        for (int j=0; j<steps; j++) {
            if (highest < samples[i+j])
                highest = samples [i+j];
            freq += samples[i + j];
        }
        freq += highest;
        
        freq /= steps+1;
        ampAvg += freq;
        (*it)->reset(i);
        (*it)->redraw(freq);

        Box b = Box();
    }
    float beat;
    for (i=0; i<40; i++) 
        beat += samples[i];
        
    beat /= i;
    glClearColor(0.1,0.5, beat*1.6, 1.0);
    curLine++;
    //delete samples;
}
