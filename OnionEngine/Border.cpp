#include "Border.h"
#include <iostream>
#include <GL/freeglut.h>

// Calculate the positions and dimensions for the border rectangles
GLfloat borderThickness = 0.5f; // Changes border thickness //1 looks better but because of the brief
GLfloat chessboardSize = 8.0f; // Changes the chessboard size
GLfloat xOffset = -borderThickness * 1.0f * chessboardSize;//4
GLfloat yOffset = -borderThickness * 1.0f * chessboardSize;//4
GLfloat width = (chessboardSize + 2 * borderThickness); //5
GLfloat height = (chessboardSize + 2 * borderThickness);//5
GLfloat zPos = 4.8f;

void Border::drawGeometry() {

    //// Draw the border using OpenGL rectangles
    //glBegin(GL_QUADS);

    //// Top border
    //glColor3f(0.0f, 0.9f, 0.2f);
    //glTexCoord2f(0.0f, 0.0f);
    ////glVertex3f(xOffset, yOffset, zPos);
    //glVertex3f(-4.8, -4.8, 4.8);

    //glTexCoord2f(1.0f, 0.0f);
    ////glVertex3f(xOffset + width, yOffset, zPos);
    //glVertex3f(4.8, -4.8, 4.8);

    //glTexCoord2f(1.0f, 1.0f);
    ////glVertex3f(xOffset + width, yOffset + borderThickness, zPos);
    //glVertex3f(4.8, 4.8, 4.8);

    //glTexCoord2f(0.0f, 1.0f);
    ////glVertex3f(xOffset, yOffset + borderThickness, zPos);
    //glVertex3f(-4.8, 4.8, 4.8);

    ////// Bottom border
    ////glColor3f(0.9f, 0.2f, 0.0f);
    ////glVertex3f(xOffset, yOffset + height - borderThickness, zPos);
    ////glVertex3f(xOffset + width, yOffset + height - borderThickness, zPos);
    ////glVertex3f(xOffset + width, yOffset + height, zPos);
    ////glVertex3f(xOffset, yOffset + height, zPos);



    ////// Left border
    ////glColor3f(0.0f, 0.5f, 0.8f);
    ////glVertex3f(xOffset, yOffset + borderThickness, zPos);
    ////glVertex3f(xOffset + borderThickness, yOffset + borderThickness, zPos);
    ////glVertex3f(xOffset + borderThickness, yOffset + height - borderThickness, zPos);
    ////glVertex3f(xOffset, yOffset + height - borderThickness, zPos);


    ////// Right border
    ////glColor3f(0.8f, 0.1f, 0.8f);
    ////glVertex3f(xOffset + width - borderThickness, yOffset + borderThickness, zPos);
    ////glVertex3f(xOffset + width, yOffset + borderThickness, zPos);
    ////glVertex3f(xOffset + width, yOffset + height - borderThickness, zPos);
    ////glVertex3f(xOffset + width - borderThickness, yOffset + height - borderThickness, zPos);

    //glEnd();
    glBegin(GL_QUADS); {
        //front face
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 0);
        glVertex3f(-1, -1, 1);

        glTexCoord2f(1, 0);
        glVertex3f(1, -1, 1);

        glTexCoord2f(1, 1);
        glVertex3f(1, 1, 1);

        glTexCoord2f(0, 1);
        glVertex3f(-1, 1, 1);

        //back face
        glTexCoord2f(0, 0);
        glVertex3f(1, -1, -1);

        glTexCoord2f(1, 0);
        glVertex3f(-1, -1, -1);

        glTexCoord2f(1, 1);
        glVertex3f(-1, 1, -1);

        glTexCoord2f(0, 1);
        glVertex3f(1, 1, -1);

        //left face
        glTexCoord2f(0, 0);
        glVertex3f(-1, -1, -1);

        glTexCoord2f(1, 0);
        glVertex3f(-1, -1, 1);

        glTexCoord2f(1, 1);
        glVertex3f(-1, 1, 1);

        glTexCoord2f(0, 1);
        glVertex3f(-1, 1, -1);

        //right face
        glTexCoord2f(0, 0);
        glVertex3f(1, -1, 1);

        glTexCoord2f(1, 0);
        glVertex3f(1, -1, -1);

        glTexCoord2f(1, 1);
        glVertex3f(1, 1, -1);

        glTexCoord2f(0, 1);
        glVertex3f(1, 1, 1);

        //top face
        glTexCoord2f(0, 0);
        glVertex3f(-1, 1, 1);

        glTexCoord2f(1, 0);
        glVertex3f(1, 1, 1);

        glTexCoord2f(1, 1);
        glVertex3f(1, 1, -1);

        glTexCoord2f(0, 1);
        glVertex3f(-1, 1, -1);

        //bottom face
        glTexCoord2f(0, 0);
        glVertex3f(-1, -1, -1);

        glTexCoord2f(1, 0);
        glVertex3f(1, -1, -1);

        glTexCoord2f(1, 1);
        glVertex3f(1, -1, 1);

        glTexCoord2f(0, 1);
        glVertex3f(-1, -1, 1);

    }
    glEnd();
}

