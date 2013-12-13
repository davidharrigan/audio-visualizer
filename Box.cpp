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
        glColor4f( color->r, color->g, color->b, 0.6 ); 
        glTranslatef( xLoc, yLoc+(ySize/2), zLoc );
        glRotatef( angle, dxRot, dyRot, dzRot );
        glScalef( xSize, ySize, zSize );
        glutSolidCube(length);
    glPopMatrix();
}
