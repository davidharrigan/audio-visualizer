#include "VBar.h"
#include <math.h>


// Constructor
//----------------------------------------------------
VBar::VBar() {
    xLoc = yLoc = zLoc = 0;
    xSize = ySize = zSize = 0;
    opacity = 0.8;
    color = new Color(0,0,0);
    childCount = 0;

}


// Destructor
//----------------------------------------------------
VBar::~VBar() {

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
    if (ySize > 0) {
        glPushMatrix();
            glColor3f(color->r, color->g, color->b);
            glTranslatef(xLoc, yLoc + (ySize/2), zLoc);
            glScalef(xSize, ySize, zSize);
            //glutSolidDodecahedron();
            glutSolidCube(1);
        /*
        GLfloat data[] = { 
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f
        };
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, 8, data);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 11);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        */
        glPopMatrix();
        int i;
        for (i=0, iter = children.begin(); i<childCount; i++, iter++) 
            (*iter)->redraw();

    }
 /* 
    int i;
    for (i=0, iter = children.begin(); i < childCount; i++, iter++)
       (*iter)->redraw();
       */
}

void VBar::createChildren(int maxChildren) {
    for (int i=1; i<maxChildren+1; i++) {
        VBar* v = new VBar();
        v->setLocation(xLoc, yLoc, zLoc);
        v->setSize(xSize+(xSize*(1+i)*1.5), ySize, zSize);
        children.push_back(v);
    }
}
