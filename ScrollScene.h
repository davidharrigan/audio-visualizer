/**
 * ScrollScene.h - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */
#ifndef SCROLL_SCENE_H_
#define SCROLL_SCENE_H_

#include <vector>
#include <string>
#include "opengl.h"
#include "VBar.h"
#include "Audio.h"

class ScrollScene {
public:
    ScrollScene();

    void addObject( VBar* object );
    void clear();
    void redraw();
    
protected:
    //objects collection
    std::vector<std::vector<VBar*>*> lines;
    std::vector<VBar*> cubes;
    
    int sampleSize; 
    int steps; 
    int numBars;
    unsigned int curLine;
};
#endif /*SCENE_H_*/
