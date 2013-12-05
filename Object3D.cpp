//
// Object3D.cpp - an abstract class representing an OpenGL graphical object
//
// David Harrigan
// 11/28/2013
//
#include "Object3D.h"
#include <iostream>
#include "Color.h"

//
// Create a new object3D at position 0,0,0 of size 1,1,1
//
Object3D::Object3D() {
    color = new Color( 1.0, 0.0, 0.0 ); //red is default
    setLocation( 0, 0, 0 );
    setSize( 1, 1, 1 );
    setRotate( 0, 0, 0, 0);
}

// Destructor
Object3D::~Object3D() { }

void Object3D::moveUp() {
    zLoc -= zSize;
    if( ySize > 0.01) 
        ySize -= 0.001;
    trans -= 0.01;
}

void Object3D::reset(int loc) {
    //zLoc = loc*zSize;
    zLoc = 2;
}

//
// set the location of the object to the x,y,z position defined by the args
//
void Object3D::setLocation( float x, float y, float z ) {
    xLoc = x;
    yLoc = y;
    zLoc = z;
}

//
// Sets the object's size
//
void Object3D::setSize( float xs, float ys, float zs ) {
    xSize = xs;
    ySize = ys;
    zSize = zs;
}

//
// set the rotation of the object
//
void Object3D::setRotate( float a, float dx, float dy, float dz ) {
    angle = a;
    dxRot = dx;
    dyRot = dy;
    dzRot = dz;
}

//
// Sets the object's color
//
void Object3D::setColor(Color* c ) {
    color = c;
}

//
// return the location as a Point3 object
//
Point3* Object3D::getLocation() {
    return new Point3(xLoc, yLoc, zLoc);
}

//
// return the size as a Point3 object
//
Point3* Object3D::getSize() {
    return new Point3(xSize, ySize, zSize);
}
