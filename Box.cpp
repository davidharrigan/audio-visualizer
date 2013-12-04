#include "Box.h"
#include <stdio.h>

Box::Box() {
    length = 1;
    ySize = 0;
}

Box::~Box(){ }

void Box::redraw(float freq) {   
//    printf("%.4f\n", freq);
    ySize = freq ;
    glPushMatrix();
        glColor3f( color->r, color->g, color->b ); 
        glTranslatef( xLoc, yLoc+(ySize/2), zLoc );
        glRotatef( angle, dxRot, dyRot, dzRot );
        glScalef( xSize, ySize, zSize );
        glutSolidCube( length );
    glPopMatrix();
}
