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
#include "fft.h"

class Scene {
public:
    Scene();

    void addObject( Object3D* object );
    void addObject2( Object3D* object );
    void clear();
    void redraw();
    
protected:
    int getLatestBufferIndex();
    //objects collection
    std::vector<Object3D*> objects;
    std::vector<Object3D*> objects2;

    //fft object
    fft* fftObject;
};
#endif /*SCENE_H_*/
