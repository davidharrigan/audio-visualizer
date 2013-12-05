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
#include "Object3D.h"
#include "Audio.h"

class Scene {
public:
    Scene();

    void addObject( Object3D* object );
    void clear();
    void redraw();
    
protected:
    //objects collection
    std::vector<std::vector<Object3D*>*> lines;
    
    int sampleSize; 
    int steps; 
    int numBars;
    int curLine;
};
#endif /*SCENE_H_*/
