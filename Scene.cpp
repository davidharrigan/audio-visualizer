/**
 * Scene.cpp - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */

#include "Scene.h"

#include <fmodex/fmod.h>
#include <iostream>
#include <GL/glui.h>
#include "Audio.h"
#include "Box.h"

char noise[128][128][3];
//GLubyte *noise;
GLuint textureID;
GLUquadric* quadric;

void generateNoise() {
    for (int x=0; x<128; x++) {
        for (int y=0; y<128; y++) {
            noise[x][y][0] = (char)((rand() % 32768) / 32768.0);
            noise[x][y][1] = (char)((rand() % 32768));
            noise[x][y][2] = (char)((rand() % 32768) / 32768.0);
        }
    }
}

// Constructors
// ------------------------------------------------------------------

Scene::Scene() {
    sampleSize = 4096; //2028, 4096, and 8192 are good
    steps = 3;
    numBars = 100;
    float size = 2.0 / numBars;
    for (int i=0; i<numBars; i++) {
        Box *b = new Box();
        b->setSize(size, 0, size);
        b->setColor(new Color(0,0,0));
        b->setLocation(1-i*size, 0, 0);
        objects.push_back(b);
    }
    numBars = 200;
    size = 2.0 / numBars;
    for (int i=0; i<numBars; i++) {
        Box *b = new Box();
        b->setSize(size, 0, size);
        b->setColor(new Color(0,0,0));
        b->setLocation(1-i*size, 0, 0);
        objects2.push_back(b);
    }

    quadric = gluNewQuadric();
    generateNoise();
    textureID = 0;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR, GL_UNSIGNED_BYTE, noise);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluQuadricTexture(quadric, GLU_TRUE);
}


// Public Methods
// ------------------------------------------------------------------

//
// Redraws the scene
//
void Scene::redraw() {
    glPushMatrix();
    glTranslatef(0, -1, 0);
    int i;
    float ampAvg = 0;
    float* samples = getSoundSpectrum(sampleSize);

    for (i=10, it = objects.rbegin(); it != objects.rend(); i+=steps, it++) {
        float freq = 0;
        for (int j=0; j<steps; j++) {
            freq += samples[i + j];
            ampAvg += freq;
        }
        freq /= steps;
        (*it)->redraw(freq);
    }
    ampAvg /= i;
    glTranslatef(0,-0.005,0);
    glRotatef(90,1,0,0);
   
    for (it=objects2.rbegin(); it != objects2.rend(); i+= steps, it++) {
        float freq = 0;
        for (int j=0; j<steps; j++) 
            freq += samples[i + j];

        freq /= steps; 
        (*it)->redraw(freq);
    }
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBegin(GL_QUADS);
            glVertex3f(-1,-1,0);
            glTexCoord3f(-1,-1,0);
            glVertex3f(-1,1,0);
            glTexCoord3f(-1,1,0);
            glVertex3f(1,1,0);
            glTexCoord3f(1,1,0);
            glVertex3f(1,-1,0);
            glTexCoord3f(1,-1,0);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //glClearColor(0,0, ampAvg*0.2, 1.0);
}
