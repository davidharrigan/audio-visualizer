#ifndef VBAR_H_
#define VBAR_H_

#include <vector>
#include "opengl.h"

class VBar {

public:
    VBar();
    ~VBar();

    // setters
    void setLocation(float x, float y, float z);
    void setSize(float xs, float ys, float zs);
    void setHeight(float freq);

    // animation
    void moveUp();
    void moveUp(float);
    void reset();
    void redraw();

    void buildBuffers();
    void buildShaders();
    void createChildren(int);
  
private:

    float xLoc, yLoc, zLoc;
    float xSize, ySize, zSize;
    float height;
    glm::vec4  color;
    float opacity;

    GLuint vertexbuffer, colorbuffer;
    GLuint vPositionID;
    GLuint matrixID;
    GLuint colorID; 
    GLuint vertexArrayID;
    GLuint moveID;

    std::vector<VBar*> children;  
    std::vector<VBar*>::iterator iter;
    int childCount;

};
#endif
