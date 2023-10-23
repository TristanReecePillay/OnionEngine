#include "Border.h"
#include <iostream>
#include <GL/freeglut.h>


void Border::drawGeometry() {

    glBegin(GL_QUADS); {
        //front face
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 0);
        glVertex3f(-10, 4.2, 10);

        glTexCoord2f(1, 0);
        glVertex3f(10, 4.2, 10);

        glTexCoord2f(1, 1);
        glVertex3f(10, 4.8, 10);

        glTexCoord2f(0, 1);
        glVertex3f(-10, 4.8, 10);

        //back face
        glTexCoord2f(0, 0);
        glVertex3f(10, 4.2, -10);

        glTexCoord2f(1, 0);
        glVertex3f(-10, 4.2, -10);

        glTexCoord2f(1, 1);
        glVertex3f(-10, 4.8, -10);

        glTexCoord2f(0, 1);
        glVertex3f(10, 4.8, -10);

        //left face
        glTexCoord2f(0, 0);
        glVertex3f(-10, 4.2, -10);

        glTexCoord2f(1, 0);
        glVertex3f(-10, 4.2, 10);

        glTexCoord2f(1, 1);
        glVertex3f(-10, 4.8, 10);

        glTexCoord2f(0, 1);
        glVertex3f(-10, 4.8, -10);

        //right face
        glTexCoord2f(0, 0);
        glVertex3f(10, 4.2, 10);

        glTexCoord2f(1, 0);
        glVertex3f(10, 4.2, -10);

        glTexCoord2f(1, 1);
        glVertex3f(10, 4.8, -10);

        glTexCoord2f(0, 1);
        glVertex3f(10, 4.8, 10);

        //top face
        glTexCoord2f(0, 0);
        glVertex3f(-10, 4.8, 10);

        glTexCoord2f(1, 0);
        glVertex3f(10, 4.8f, 10);

        glTexCoord2f(1, 1);
        glVertex3f(10, 4.8f, -10);

        glTexCoord2f(0, 1);
        glVertex3f(-10, 4.8f, -10);

        //bottom face
        glTexCoord2f(0, 0);
        glVertex3f(-10, 4.2, -10);

        glTexCoord2f(1, 0);
        glVertex3f(10, 4.2, -10);

        glTexCoord2f(1, 1);
        glVertex3f(10, 4.2, 10);

        glTexCoord2f(0, 1);
        glVertex3f(-10, 4.2, 10);

    }
    glEnd();
}

