/**
 * Scene.h - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>
#include <GL/glut.h>
#include "Box.h"
#include "Audio.h"

class Scene {
public:
    Scene();

    void addObject( Box* object );
    void clear();
    void redraw();
    
protected:
    //objects collection
    std::vector<Box*> objects;
    std::vector<Box*> objects2;
    std::vector<Box*>::reverse_iterator it;
    
    GLuint textureID;
    int sampleSize; 
    int steps; 
    int numBars;
    int curLine;

};
#endif /*SCENE_H_*/
