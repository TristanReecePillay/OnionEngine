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
    // topmost cylinder (head)
    glPushMatrix();
    //glColor3f(0.5f, 0.0f, 0.8f); //purple
    glTranslatef(0.0, 6.0, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic, 0.3f, 0.1f, 1.5f, 22, 22);
    glScalef(1.0f, 1.0f, 0.01f);
    glutSolidTorus(0.27f, 0.15f, 12, 12);
    glPopMatrix();

    // middle cylinder (body)
    glPushMatrix();
    //glColor3f(0.2f, 1.0f, 0.2f);//green
    glTranslatef(0.0f, 3.5f, 0.0f);
    quadratic = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.6f, 0.3f, 3.0f, 12, 12);
    glPopMatrix();

    // top covering (body)
    glPushMatrix();
   // glColor3f(1.0f, 0.0f, 0.0f);//red
    glTranslatef(0.0f, 6.5f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0f, 1.0f, 0.1f);
    glutSolidTorus(0.2f, 0.15f, 32, 32);
    glPopMatrix();

    // Base Cylinder
    glPushMatrix();
    //glColor3f(0.9f, 0.2f, 0.5f);//pink
    glTranslatef(0.0f, 4.5f, 0.0f);
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.9f, 0.9f, 1.0f, 12, 12);
    glPopMatrix();

     //base middle covering
        glPushMatrix();
        //glColor3f(0.1f, 0.2f, 0.8f); //blue
        glTranslatef(0.0, 4.5f, 0.0);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(1.0f, 1.0f, 0.3f);
        glutSolidTorus(0.6f, 0.3f, 32, 32);
        glPopMatrix();

}