#include "VBar.h"
#include <math.h>
#include <stdio.h>

using namespace glm;


extern int checkGLerror(const char*, bool quit=false);
extern glm::mat4 MVP;
extern GLuint shaderProgram;

GLfloat move[] = {
    0,0,1
};

GLfloat data[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, -0.96875f,
    -1.0f, 1.0f, -0.96875f,
     -0.96875f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     -0.96875f,-1.0f, -0.96875f,
    -1.0f,-1.0f,-1.0f,
     -0.96875f,-1.0f,-1.0f,
     -0.96875f, 1.0f,-1.0f,
     -0.96875f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, -0.96875f,
    -1.0f, 1.0f,-1.0f,
     -0.96875f,-1.0f, -0.96875f,
    -1.0f,-1.0f, -0.96875f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, -0.96875f,
    -1.0f,-1.0f, -0.96875f,
     -0.96875f,-1.0f, -0.96875f,
     -0.96875f, 1.0f, -0.96875f,
     -0.96875f,-1.0f,-1.0f,
     -0.96875f, 1.0f,-1.0f,
     -0.96875f,-1.0f,-1.0f,
     -0.96875f, 1.0f, -0.96875f,
     -0.96875f,-1.0f, -0.96875f,
     -0.96875f, 1.0f, -0.96875f,
     -0.96875f, 1.0,-1.0f,
    -1.0f, 1.0f,-1.0f,
     -0.96875f, 1.0f, -0.96875f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, -0.96875f,
     -0.96875f, 1.0f, -0.96875f,
    -1.0f, 1.0f, -0.96875f,
     -0.96875f,-1.0f, -0.96875f

};    

GLfloat colors[] = {
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.585f, 0.771f, 0.014f, 
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.666f, 0.430f, 0.123f,
    0.342f, 0.434f, 0.434f,
    0.342f, 0.434f, 0.434f,
};

// Constructor
//----------------------------------------------------
VBar::VBar() {
    xLoc = yLoc = zLoc = 0;
    xSize = ySize = zSize = 0;
    childCount = 0;
    opacity = 0.8;
    color = vec4(1,0,0,0);

    buildShaders();
    buildBuffers();
}


// Destructor
//----------------------------------------------------
VBar::~VBar() {
}

// VAO
//----------------------------------------------------

//
// Initialize the vertex position attribute from the vertex shader
//
//
void VBar::buildBuffers() {
  
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Get a handle of the MVP uniform
    matrixID = glGetUniformLocation(shaderProgram, "MVP");
    moveID = glGetUniformLocation(shaderProgram, "move");
    
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STREAM_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STREAM_DRAW);
}

//
//
//
void VBar::buildShaders() {
}

// Public Methods
//----------------------------------------------------
void VBar::setLocation(float x, float y, float z) {
    xLoc = x; 
    yLoc = y; 
    zLoc = z;
}

void VBar::setSize(float xs, float ys, float zs) {
    xSize = xs;
    ySize = ys;
    zSize = zs;
}

void VBar::setHeight(float freq) {
    float offset;
    if (freq > 0.8) freq = 0.8; //limit the max height
    else ySize = freq;

    //
    int i;
    for (i=1, iter = children.begin(); i < childCount+1; iter++, i++)
       (*iter)->setHeight(freq-offset*i*2);
}

void VBar::moveUp() {
    zLoc -= zSize;
    opacity -= 0.2;

    int i;
    for (i=0, iter = children.begin(); i < childCount; i++, iter++)
       (*iter)->moveUp(zSize);
}

void VBar::moveUp(float step) {
    zLoc -= step;
    opacity -= 0.001;
}

void VBar::reset() {
    zLoc = 2;
    opacity = 1;

    for (iter = children.begin(); iter != children.end(); iter++)
       (*iter)->reset();
}

void VBar::redraw() {
    for (int i=1; i < 12*3*3; i+=1) {
        data[i] += 0.2;
    }

    glUseProgram(shaderProgram);

    // Send transformation to the currently bound shader 
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniform4fv(moveID, 1, move);

    // Vertex
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Color
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


 /* 
    int i;
    for (i=0, iter = children.begin(); i < childCount; i++, iter++)
       (*iter)->redraw();
       */
}

void VBar::createChildren(int maxChildren) {
    return;
    /*for (int i=1; i<maxChildren+1; i++) {
        VBar* v = new VBar();
        v->setLocation(xLoc, yLoc, zLoc);
        v->setSize(xSize+(xSize*(1+i)*1.5), ySize, zSize);
        children.push_back(v);
    }*/
}
