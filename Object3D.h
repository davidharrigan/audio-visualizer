#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include <vector>
#include <GL/glut.h>
#include "Color.h"
#include "Point3.h"

class Object3D {
public:
    Object3D();
    virtual ~Object3D();
    
    // Setters 
    void setLocation(float x, float y, float z);
    void setSize(float xs, float ys, float zs);   
    void setRotate(float angle, float dx, float dy, float dz);
    void setColor(Color* c);

    // Getters 
    Point3* getLocation();             
    Point3* getSize();
    
    virtual void redraw(float) = 0;
    
protected:
    float xLoc, yLoc, zLoc;        // location (origin) of the object
    float xSize, ySize, zSize;     // size of the object
    float angle, dxRot, dyRot, dzRot; // rotation angle and axis
    Color* color;
};

#endif /*OBJECT3D_H_*/

