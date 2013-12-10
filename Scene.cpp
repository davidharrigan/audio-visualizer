/**
 * Scene.cpp - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */

#include "Scene.h"

#include <iostream>
#include <GL/glui.h>
#include "Audio.h"
#include "Box.h"

//GLubyte *noise;
//char noise[512][512][3];
GLUquadric* quadric;

//
// 
//
void generateNoise(float samples[], GLubyte noise[1024][1024][3]) {
    for (int y=0; y<1024; y++) {
        for (int x=0; x<1024; x++) {
            float freq = samples[x*y % 4096];
            //noise[x][y][0] = freq[x*y%100] * 10000;
            //noise[x][y][1] = freq[x*y%100] * 30000;
            //noise[x][y][2] = freq[x*y%100] * 40000;
            if (freq < 0.01) {
                noise[x][y][0] = 0x00; // R
                noise[x][y][1] = 0x00; // G
                noise[x][y][2] = 0xff; // B
            } 
            else if (freq < 0.1) {
                noise[x][y][0] = 0x60;
                noise[x][y][1] = 0xff;
                noise[x][y][2] = 0xf0;
            }
            else if (freq < 0.2) {
                noise[x][y][0] = 0x99;
                noise[x][y][1] = 0x0f;
                noise[x][y][2] = 0xaa;
            } 
            else if (freq < 0.6) {
                noise[x][y][0] = 0xff;
                noise[x][y][1] = 0xef;
                noise[x][y][2] = 0xff;
            }
            else {
                noise[x][y][0] = 0xff;
                noise[x][y][1] = 0xff;
                noise[x][y][2] = 0xff;
            }
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
    textureID = 0;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

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

    //glDeleteTextures(1, &textureID);
    GLubyte noise[1024][1024][3];
    generateNoise(samples, noise);
    //glRasterPos3i(0.5, 0.5, 0.3);
    //glDrawPixels(512,512,GL_RGB, GL_UNSIGNED_BYTE, noise);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE,noise);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPushMatrix();
        glBegin(GL_QUADS);
            glVertex3f(-1,-1,0);
            glTexCoord2i(-1,-1);
            glVertex3f(-1,1,0);
            glTexCoord2i(-1,1);
            glVertex3f(1,1,0);
            glTexCoord2i(1,1);
            glVertex3f(1,-1,0);
            glTexCoord2i(1,-1);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //glClearColor(0,0, ampAvg*0.2, 1.0);
}
