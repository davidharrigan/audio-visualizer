/**
 * ScrollScene.cpp - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */

#include "ScrollScene.h"

#include <iostream>
#include "Audio.h"
#include "VBar.h"

// Constructors
// ------------------------------------------------------------------

ScrollScene::ScrollScene() {
    curLine = 0;
    sampleSize = 2086;
    numBars = 24;
    float size = 2.0 / (numBars*8);
    for (int i=0; i<numBars*2; i++) {
        std::vector<VBar*>* temp = new std::vector<VBar*>();
        for (int j=0; j<numBars; j++) {
            VBar *b = new VBar();
            b->setSize(size, 0, size*4);
            b->setLocation(1-j*size*5, 0, 1-i*size + 2);
            temp->push_back(b); 
            b->createChildren(10);
        }
        lines.push_back(temp);
    }
}


// Public Methods
// ------------------------------------------------------------------

//
// Redraws the scene
//
void ScrollScene::redraw() {
    unsigned int i;
    float* samples = new float[24];
    if (curLine >= lines.size())
        curLine = 0;

    glTranslatef(0.5, 0, 1);
    std::vector<VBar*> objects = *lines[curLine];
    std::vector<VBar*>::reverse_iterator it;
    std::vector<std::vector<VBar*>* >::iterator itt;

    // get sound spectrum
    for (i=0; i<24; i++) 
        samples[i] = 0;
    getSoundSpectrum(24, samples);

    // move up all lines
    for (i=0, itt=lines.begin(); itt != lines.end(); itt++, i++) {
        for (it=(*itt)->rbegin(); it!=(*itt)->rend(); it++) {
            (*it)->moveUp();
            (*it)->redraw();
        }
    }
   
    // redraw samples for current line
    for (i=0, it = objects.rbegin(); it != objects.rend(); i++, it++) {
        float freq = samples[i];
        (*it)->setHeight(freq);
        (*it)->reset();
        (*it)->redraw();
    }

    curLine++;
    delete samples;
}
