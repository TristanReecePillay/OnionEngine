#include "Pawn.h"
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Pawn::drawGeometry() 
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    // glScalef(0.2f, 0.2f, 0.2f);


    GLUquadricObj* quadratic;
    // topmost cylinder
    glPushMatrix();
    //glColor3f(1.0f, 1.0f, 1.0f); //purple
    glTranslatef(0.0, 6.0, 0.0);  //make king 6.5
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluQuadricTexture(quadratic, GL_TRUE); 
    gluCylinder(quadratic, 0.8f, 0.8f, 0.2f, 22, 22);
    glScalef(1.0f, 1.0f, 0.001f);
    glutSolidTorus(0.42f, 0.42f, 12, 12);
    glPopMatrix();

    // Base covering
    glPushMatrix();
    //glColor3f(1.0f, 1.0f, 1.0f);//red
    glTranslatef(0.0f, 4.5f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 0.1);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glutSolidTorus(0.4f, 0.5f, 32, 32);
    glPopMatrix();

    // middle cylinder
    glPushMatrix();
    //glColor3f(1.0f, 1.0f, 1.0f);//green (will also be White)
    glTranslatef(0.0f, 3.5f, 0.0f);
    quadratic = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluQuadricTexture(quadratic, GL_TRUE); 
    gluCylinder(quadratic, 0.7f, 0.1f, 2.2f, 12, 12);
    glPopMatrix();

    // Base
    glPushMatrix();
    //glColor3f(1.0f, 1.0f, 1.0f);//pink
    glTranslatef(0.0f, 4.5f, 0.0f);
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluQuadricTexture(quadratic, GL_TRUE); 
    gluCylinder(quadratic, 0.9f, 0.9f, 1.0f, 12, 12);
    glPopMatrix();

    //sphere
    glTranslatef(0.0f, 6.5f, 0.0f);
    //glColor3f(1.0, 1.0, 1.0); // Set color to white (for proper texture rendering)
    const int stacks = 20;
    const int slices = 20;
    const float radius = 0.5f;

    for (int i = 0; i < stacks; ++i) {
        float theta1 = (i / (float)(stacks - 1)) * M_PI;
        float theta2 = ((i + 1) / (float)(stacks - 1)) * M_PI;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float phi = (j / (float)slices) * (2 * M_PI);

            // Calculate texture coordinates
            float u = j / (float)slices;
            float v1 = 1.0 - i / (float)(stacks - 1);
            float v2 = 1.0 - (i + 1) / (float)(stacks - 1);

            glTexCoord2f(u, v1);
            glVertex3f(radius * sin(theta1) * cos(phi), radius * sin(theta1) * sin(phi), radius * cos(theta1));

            glTexCoord2f(u, v2);
            glVertex3f(radius * sin(theta2) * cos(phi), radius * sin(theta2) * sin(phi), radius * cos(theta2));
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);  
    glDisable(GL_TEXTURE_GEN_S);  
    glDisable(GL_TEXTURE_GEN_T);  
    //glPopMatrix();
}