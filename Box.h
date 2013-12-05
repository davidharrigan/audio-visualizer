
#ifndef BOX_H_
#define BOX_H_

#include <iostream>
#include "Object3D.h"

class Box: public Object3D
{
public:
    Box();
    virtual ~Box();
   
    virtual void redraw(float);
    void moveUp();
   
protected:

    Box *b;
    float length;
    Color colors[3];
};

#endif /*BOX_H_*/
