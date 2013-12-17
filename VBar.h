#ifndef VBAR_H_
#define VBAR_H_
#define GL_GLEXT_PROTOTYPES

#include <vector>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Color.h"

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
    void sendToShader();
    void createChildren(int);
  
private:

    float xLoc, yLoc, zLoc;
    float xSize, ySize, zSize;
    float height;
    Color *color;
    float opacity;
    GLuint id, vertexBuffer;
    GLuint shaderProgram;

    std::vector<VBar*> children;  
    std::vector<VBar*>::iterator iter;
    int childCount;

    GLfloat data[36*3] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f

    };    
};


#endif
