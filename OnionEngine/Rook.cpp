#include "Rook.h"
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

void Rook::drawGeometry() {

    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);

    //glScalef(0.0f, 0.0f, 0.0f);
    GLUquadricObj* quadratic;
    // topmost cylendar
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f); //purple
    glTranslatef(0.0, 8.0, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 1.0f, 1.0f, 1.0f, 12, 12);
    //glRotated(-90, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 0.5);
    glutSolidTorus(0.9f, 0.1f, 50, 50);
    glPopMatrix();
    
    // top covering
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);//red
    glTranslatef(0.0, 0.5, 0.0);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 0.1);
    glutSolidTorus(0.9f, 0.1f, 50, 50);
    glPopMatrix();

    // middle cylendar
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 0.5f);//green
    glTranslatef(0.0, 1.0, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 1.0f, 0.6f, 3.4f, 32, 32);
    glPopMatrix();

    // inverted cylendar
    glPushMatrix();
    glColor3f(0.9f, 0.2f, 0.5f);//pink
    glTranslatef(0.0, 5.5, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.85f, 0.55f, 3.4f, 32, 32);
    glPopMatrix();

    // middle covering
    glPushMatrix();
    glColor3f(0.1f, 0.2f, 0.8f); //blue
    glTranslatef(0.0, 5.4, 0.0);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 3.5);
    glutSolidTorus(0.455f, 0.3f, 50, 50);
    glPopMatrix();


    //glEnd();
}