#include "VBar.h"
#include <math.h>
#include "makeShader.h"


// Constructor
//----------------------------------------------------
VBar::VBar() {
    xLoc = yLoc = zLoc = 0;
    xSize = ySize = zSize = 0;
    childCount = 0;
    opacity = 0.8;
    color = new Color(0,0,0);

    buildShaders();
    buildBuffers();
}


// Destructor
//----------------------------------------------------
VBar::~VBar() {
}

// VAO
//----------------------------------------------------
void VBar::buildBuffers() {
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
    
    // Create buffer objects
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetUniformLocation(shaderProgram, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
    GLuint pmv = glGetAttribLocation(shaderProgram, "projXmv");
    glEnableVertexAttribArray(pmv);
    glVertexAttribPointer(pmv, 2, GL_DOUBLE, GL_FALSE, 0, BUFFER_OFFSET(0));
}

void VBar::buildShaders() {
    shaderProgram = makeShaderProgram("vertex.vsh", "color.fsh");
    glUseProgram(shaderProgram);
}

void VBar::sendToShader() {
    GLfloat modelview[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMultMatrixf(modelview);

    GLfloat PtimesMV[16];
    glGetFloatv(GL_PROJECTION_MATRIX, PtimesMV);
    glPopMatrix();

    GLint matLoc = glGetUniformLocation(shaderProgram, "projXmv");
    glUniformMatrix4fv(matLoc, 1, false, PtimesMV);
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

    // decide color
    if (freq < 0.01) {
        ySize = 0;
        color->set(0, 0, 0);
        opacity = 0;
        offset = 0;
    }
    else if(freq < 0.2) {
        color->set(1.0 * freq * 4, 0.1, 1.0);
        offset = 0.01;
    }
    else if(freq < 0.4) {
        color->set(0.4 * freq * 1.2, 
                   1.0 * freq * 2, 
                   1.0);
        offset = 0.02;
    }
    else if(freq < 0.6) {
        color->set(0.4 * freq * 1.2, 
                   1.0 * freq * 2, 
                   1.0);
        offset = 0.04;
    }
    else {
        color->set(0.4 * freq , 1.5 * freq, 0.4);
        offset = 0.06;
    }

    if (children.size() > 0 && freq > 0.01) {
        childCount = (freq * 8);
    } else {
        childCount = 0;
    }
    
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
    printf("redraw\n");
        sendToShader();
    
        //GLint colorLoc = glGetUniformLocation(shaderProgram, "color");
        //glUniform4fv(colorLoc, 1, color);
        glBindVertexArray(vertexBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glBindVertexArray(0);
 /* 
    int i;
    for (i=0, iter = children.begin(); i < childCount; i++, iter++)
       (*iter)->redraw();
       */
}

void VBar::createChildren(int maxChildren) {
    return;
    for (int i=1; i<maxChildren+1; i++) {
        VBar* v = new VBar();
        v->setLocation(xLoc, yLoc, zLoc);
        v->setSize(xSize+(xSize*(1+i)*1.5), ySize, zSize);
        children.push_back(v);
    }
}
