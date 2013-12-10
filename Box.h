
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
    GLfloat vertices [72] = {
                    // front
                    -1.0f, -1.0f, 1.0f,
                    1.0f, -1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f, 
                    -1.0f, 1.0f, 1.0f,
    
                    // top
                    -1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, -1.0f,
                    -1.0f, 1.0f, -1.0f,
    
                    // back
                    1.0f, -1.0f, -1.0f,
                    -1.0f, -1.0f, -1.0f,
                    -1.0f, 1.0f, -1.0f,
                    1.0f, 1.0f, -1.0f, 

                    // bottom
                    -1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, -1.0f, 1.0f,
                    -1.0f, -1.0f, 1.0f,

                    // left
                    -1.0f, -1.0f, -1.0f,
                    -1.0f, -1.0f, 1.0f,
                    -1.0f, 1.0f, 1.0f,
                    -1.0f, 1.0f, -1.0f,

                    // right
                    1.0f, -1.0f, 1.0f,
                    1.0f, -1.0f, -1.0f,
                    1.0f, 1.0f, -1.0f,
                    1.0f, 1.0f, 1.0f
                  };
    GLfloat texcoords [72] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };
};

#endif /*BOX_H_*/
