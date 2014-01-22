#include "VBar.h"
#include <math.h>
#include <stdio.h>

using namespace glm;

extern int checkGLerror(const char*, bool quit=false);
extern glm::mat4 MVP;
extern GLuint shaderProgram;

static GLfloat data[] = {
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
     1.0f, 1.0,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
};    

// Constructor
//----------------------------------------------------
VBar::VBar() {
    childCount = 0;
    color = vec4(0,0,0,0);
    setLocation(0,0,0);
    setSize(0,0,0);
    ch = 0;

    buildBuffers();
}


// Destructor
//----------------------------------------------------
VBar::~VBar() {
}


// Public Methods
//----------------------------------------------------

//
// Fetches glsl uniform variables and initializes attribute buffer
//
void VBar::buildBuffers() {
  
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Get a handle of the uniform variables from shader
    matrixID = glGetUniformLocation(shaderProgram, "MVP");
    translationID = glGetUniformLocation(shaderProgram, "translation");
    scaleID = glGetUniformLocation(shaderProgram, "scale");
    colorID = glGetUniformLocation(shaderProgram, "vertexColor");

    // Our input
    vPositionID = glGetAttribLocation(shaderProgram, "vPosition");
    
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void VBar::setLocation(float x, float y, float z) {
    xLoc = x; 
    yLoc = y; 
    zLoc = z;

    translationMatrix = glm::translate(x, y, z);
}

void VBar::setSize(float xs, float ys, float zs) {
    xSize = xs;
    ySize = ys;
    zSize = zs;

    scaleMatrix = glm::scale(xs, ys, zs);
}

void VBar::setHeight(float freq) {
    freq = (freq > 0.8) ? 0.8 : freq;
    scaleMatrix[1][1] = freq;
    translationMatrix[3][1] += freq;

    if (freq < 0.05) 
        color = glm::vec4(0,0,0,0);
    else if (freq < 0.2) 
        color = glm::vec4(freq * 4.0f, 0.1f, 1.0f, 1.0f);
    else if (freq < 0.4) 
        color = glm::vec4(freq * 0.5f, freq * 2.0f, 1.0f, 1.0f);
    else if (freq < 0.6)
        color = glm::vec4(freq * 0.5f, freq * 2.0f, 0.8f, 1.0f);
    else 
        color = glm::vec4(freq * 0.4f, freq * 1.5f, 0.4f, 1.0f);
}

void VBar::moveUp() {
    zLoc -= zSize + 0.05;
    translationMatrix[3][2] = zLoc;
}

void VBar::moveUp(float step) {
    zLoc -= step;
    translationMatrix[3][2] = zLoc;
}

void VBar::reset() {
    zLoc = 2; translationMatrix = glm::translate(xLoc, yLoc, zLoc);
}

void VBar::redraw() {
    for (int i=1; i < 12*3*3; i+=1) {
        data[i] += 0.2;
    }

    glUseProgram(shaderProgram);

    // Send transformation to the currently bound shader 
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(translationID, 1, GL_FALSE, &translationMatrix[0][0]);
    glUniformMatrix4fv(scaleID, 1, GL_FALSE, &scaleMatrix[0][0]);
    glUniform4fv(colorID, 1, &color[0]);

    // Vertex
    glEnableVertexAttribArray(vPositionID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(vPositionID, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glDisableVertexAttribArray(vPositionID);
}
