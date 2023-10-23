#include "King.h"
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

void King::drawGeometry()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    // glScalef(0.2f, 0.2f, 0.2f);


    GLUquadricObj* quadratic;
    // topmost cylinder
    glPushMatrix();
    glColor3f(0.5f, 0.0f, 0.8f); //purple
    glTranslatef(0.0, 7.5, 0.0);  //make king 6.5
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.2f, 0.2f, 0.8f, 22, 22); 
    glScalef(1.0f, 1.0f, 0.001f); 
    glutSolidTorus(0.2f, 0.2f, 12, 12); 
    glPopMatrix(); 

    // topmost cylinder
    glPushMatrix();
    glColor3f(0.5f, 0.0f, 0.8f); //purple
    glTranslatef(0.0, 6.5, 0.0);  //make king 6.5
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.8f, 0.8f, 0.2f, 22, 22);
    glScalef(1.0f, 1.0f, 0.001f);
    glutSolidTorus(0.42f, 0.42f, 12, 12);
    glPopMatrix();

    // Base covering
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);//red
    glTranslatef(0.0f, 4.5f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 0.1);
    glutSolidTorus(0.4f, 0.5f, 32, 32);
    glPopMatrix();

    // middle cylinder
    glPushMatrix();
    glColor3f(0.2f, 1.0f, 0.2f);//green
    glTranslatef(0.0f, 3.5f, 0.0f);
    quadratic = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.7f, 0.1f, 3.0f, 12, 12);
    glPopMatrix();

    // Base
    glPushMatrix();
    glColor3f(0.9f, 0.2f, 0.5f);//pink
    glTranslatef(0.0f, 4.5f, 0.0f);
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.9f, 0.9f, 1.0f, 12, 12);
    glPopMatrix();
}
