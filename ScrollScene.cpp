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
    float size = 2.0 / (numBars*6);
    for (int i=0; i<numBars; i++) {
        std::vector<VBar*>* temp = new std::vector<VBar*>();
        for (int j=0; j<numBars; j++) {
            VBar *b = new VBar();
            b->setSize(size, 1, size*10);
            b->setLocation(1-j*size*8, 0, 0);
            temp->push_back(b); 
            b->createChildren(8);
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
    float* samples = new float[numBars];
    if (curLine >= lines.size())
        curLine = 0;

    std::vector<VBar*> objects = *lines[curLine];
    std::vector<VBar*>::reverse_iterator it;
    std::vector<std::vector<VBar*>*>::iterator itt;

    // get sound spectrum
    for (i=0; i<numBars; i++) 
        samples[i] = 0;
    getSoundSpectrum(numBars, samples);

    // move up all lines
    for (i=0, itt=lines.begin(); itt != lines.end(); itt++, i++) {
        for (it=(*itt)->rbegin(); it != (*itt)->rend(); it++) {
            (*it)->moveUp();
            (*it)->redraw();
        }
    }

    // redraw samples for current line
    for (i=0, it = objects.rbegin(); it != objects.rend(); i++, it++) {
        (*it)->reset();
        (*it)->setHeight(samples[i]);
        (*it)->redraw();
    }

    curLine++;
    delete samples;
}
