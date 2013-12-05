#include "Box.h"
#include <stdio.h>

Box::Box() {
    length = 1;
    ySize = 0;
//    b = new Box();
//    b->setColor( new Color(1,1,1));
}

Box::~Box(){ }

void Box::moveUp() {
    zLoc += zSize;
}

void Box::redraw(float freq) {   
//    printf("%.4f\n", freq);
    if (freq != -1) {
        trans = 1;
        ySize = freq ;
        if (ySize > 1.2) 
            ySize = 1.2;
        if (freq < 0.01) {
            color->r = 0.0;
            color->b = 0.2;
            color->g = 0.2;
            ySize = 0;
        }
        else if( freq < 0.1) {
            color->r = 0.2;
            color->b = 1.0 * freq * 4;
            color->g = 0.0;
        }
        else if(freq < 0.2){
            color->r = 1.0 *freq * 4;
            color->b = 0.1;
            color->g = 1.0;
        }
        else if(freq < 0.6){
            color->r = 0.4 * freq * 1.2;
            color->g = 1.0 * freq * 2;
            color->b = 1.0;
        }
        else {
            color->r = 0.9 *freq;
            color->g = 0.3 * freq;
            color->b = 0.0;
        }
    }
    glPushMatrix();
        glColor4f( color->r, color->g, color->b, trans ); 
        glTranslatef( xLoc, yLoc+(ySize/2), zLoc );
        glRotatef( angle, dxRot, dyRot, dzRot );
        glScalef( xSize, ySize, zSize );
        glutSolidCube(length);
    glPopMatrix();

    float yOff = ySize * 0.1;
    float yOff2 = ySize * 0.2;
    glPushMatrix();
        glTranslatef( xLoc-xSize, yLoc+((ySize/2)-yOff), zLoc );
        glScalef( xSize, (ySize-yOff*2), zSize );
        glutSolidCube(length);
    glPopMatrix();

    glPushMatrix();
        glTranslatef( xLoc-xSize*2, yLoc+((ySize/2)-yOff2), zLoc );
        glScalef( xSize*2, (ySize-yOff2*2), zSize );
        glutSolidCube(length);
    glPopMatrix();

    glPushMatrix();
        glTranslatef( xLoc+xSize, yLoc+((ySize/2)-yOff), zLoc );
        glScalef( xSize, (ySize-yOff*2), zSize );
        glutSolidCube(length);
    glPopMatrix();

    glPushMatrix();
        glTranslatef( xLoc+xSize*2, yLoc+((ySize/2)-yOff2), zLoc );
        glScalef( xSize*2, (ySize-yOff2*2), zSize );
        glutSolidCube(length);
    glPopMatrix();
    //b->setSize(xSize, ySize, zSize);
 //   b->setLocation(xLoc-xSize, yLoc, zLoc);
   // b->redraw(freq-0.3);
   
/*    glPushMatrix();
        glScalef(xSize, ySize-0.01, zSize);
        glTranslatef(xLoc-0.01, yLoc+((ySize/2)-0.01), zLoc);
        glutSolidCube(length);
    glPopMatrix();

    glPushMatrix();
        glScalef(xSize, ySize-0.01, zSize);
        glTranslatef(xLoc+0.01, yLoc+((ySize/2)-0.01), zLoc);
        glutSolidCube(length);
    glPopMatrix();
    */


        /*
        glBegin(GL_QUADS);
        //Bottom
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,0,1);
        glVertex3f(0,0,1);

        //Front
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,0,0);
        
        //Left
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
        glVertex3f(0,1,1);
        glVertex3f(0,1,0);
        
        //Right
        glVertex3f(1,0,0);
        glVertex3f(1,0,1);
        glVertex3f(1,1,1);
        glVertex3f(1,1,0);

        //Back
        glVertex3f(0,0,1);
        glVertex3f(1,0,1);
        glVertex3f(1,1,1);
        glVertex3f(0,1,1);

        //Top
        glVertex3f(0,1,1);
        glVertex3f(1,1,1);
        glVertex3f(1,1,0);
        glVertex3f(0,1,0);
        glEnd();
        */
}
