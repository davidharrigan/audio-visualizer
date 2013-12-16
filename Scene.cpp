/**
 * Scene.cpp - a class represent a scene: its objects and its view
 * 
 * dtk24 - David Harrigan
 * CS770 - Fall 2013
 */

#include "Scene.h"

#include <iostream>
#include "Audio.h"
#include "Box.h"

//
// Generate texture for the background
//
void generateNoise(float samples[], GLubyte noise[1024][1024][3]) {
    for (int y=0; y<1024; y++) {
        float freq = samples[y];
        freq += samples[y+1];
        freq += samples[y+2];
        freq += samples[y+3];
        for (int x=0; x<1024; x++) {
            if (freq < 0.001) {
                noise[x][y][0] = 0x22; // R
                noise[x][y][1] = 0x22; // G
                noise[x][y][2] = 0xff; // B
            } 
            else if (freq < 0.01) {
                noise[x][y][0] = 0xee;
                noise[x][y][1] = 0xaa;
                noise[x][y][2] = 0x22;
            }
            else if (freq < 0.02) {
                noise[x][y][0] = 0xff;
                noise[x][y][1] = 0x0f;
                noise[x][y][2] = 0xaa;
            } 
            else if (freq < 0.04) {
                noise[x][y][0] = 0xff;
                noise[x][y][1] = 0x22;
                noise[x][y][2] = 0x22;
            }
            else if (freq < 0.08) {
                noise[x][y][0] = 0x00;
                noise[x][y][1] = 0xff;
                noise[x][y][2] = 0xff;
            }
            else if (freq < 0.14) {
                noise[x][y][0] = 0x22;
                noise[x][y][1] = 0x00;
                noise[x][y][2] = 0xff;
            }
            else {
                noise[x][y][0] = 0xaa;
                noise[x][y][1] = 0x00;
                noise[x][y][2] = 0xff;
            }
        }
    }
}


// Constructor
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

    GLubyte noise[1024][1024][3];
    generateNoise(samples, noise);

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
            glVertex3f(-1,1,-1);
            glTexCoord2i(-1,1);
            glVertex3f(1,1,-1);
            glTexCoord2i(1,1);
            glVertex3f(1,-1,0);
            glTexCoord2i(1,-1);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
