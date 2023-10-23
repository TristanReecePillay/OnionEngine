#include "Bishop.h"
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

void Bishop::drawGeometry()
{
    // Implement the geometry of the pawn using OpenGL commands
    // Customize the geometry to represent a pawn
    glPushMatrix();
    glScalef(0.5f, 0.5f, 1.0f); // Adjust the size as needed

    // Draw the pawn as a simple cube (you can modify this) please
    glutSolidCube(1.0f);

    glPopMatrix();
}
