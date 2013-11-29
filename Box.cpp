
#include "Box.h"


Box::Box() {
    length = 1;
}

Box::~Box(){ }

void Box::redraw() {   
    glPushMatrix();
        glColor3f( color->r, color->g, color->b ); 
        glTranslatef( xLoc, yLoc, zLoc );
        glRotatef( angle, dxRot, dyRot, dzRot );
        glScalef( xSize, ySize, zSize );
        glutSolidCube( length );
    glPopMatrix();
}
