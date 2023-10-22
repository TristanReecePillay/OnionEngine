#include "Knight.h"
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

void Knight::drawGeometry() {
	

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    // glScalef(0.2f, 0.2f, 0.2f);


    GLUquadricObj* quadratic;
    // topmost cylinder
    glPushMatrix();
    glColor3f(0.5f, 0.0f, 0.8f); //purple
    glTranslatef(0.0, 8.0, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 1.0f, 1.0f, 0.8f, 22, 22);
    glScalef(1.0f, 1.0f, 0.001f);
    glutSolidTorus(1.0f, 0.1f, 12, 12);
    glPopMatrix();
}