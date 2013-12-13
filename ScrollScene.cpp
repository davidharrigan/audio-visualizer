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
    //sampleSize = 1600; //2028, 4096, and 8192 are good
    //steps = 6;
    sampleSize = 2086;
    steps = 6;
    numBars = 32;
    float size = 2.0 / (numBars*6);
    for (int i=0; i<numBars*2; i++) {
        std::vector<VBar*>* temp = new std::vector<VBar*>();
        for (int j=0; j<numBars; j++) {
            VBar *b = new VBar();
            b->setSize(size, 0, size*4);
           // b->setColor(new Color(1,1,1));
            b->setLocation(1-j*size*6, 0, 1-i*size);
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
    if (curLine >= lines.size())
        curLine = 0;

    glTranslatef(0.5, 0, 1);
    std::vector<VBar*> objects = *lines[curLine];
    std::vector<VBar*>::reverse_iterator it;
    std::vector<std::vector<VBar*>* >::iterator itt;
    unsigned int i;
    float ampAvg = 0;
    float* samples = getSoundSpectrum(sampleSize);
    //float* samples = getSpectrum();

    // move up all lines
    for (i=0, itt=lines.begin(); itt != lines.end(); itt++, i++) {
        for (it=(*itt)->rbegin(); it!=(*itt)->rend(); it++) {
            (*it)->moveUp();
            (*it)->redraw();
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
        (*it)->setHeight(freq);
        (*it)->reset();
        (*it)->redraw();

        VBar b = VBar();
    }
    float beat;
    for (i=0; i<40; i++) 
        beat += samples[i];
        
    beat /= i;

    //glClearColor(0.1,0.5, beat*1.6, 1.0);
    curLine++;
    //delete samples;
}
