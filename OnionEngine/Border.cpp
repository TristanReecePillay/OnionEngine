#include "Border.h"
#include <iostream>
#include <GL/freeglut.h>

// Calculate the positions and dimensions for the border rectangles
GLfloat borderThickness = 0.5f; // Changes border thickness //1 looks better but because of the brief
GLfloat chessboardSize = 8.0f; // Changes the chessboard size
GLfloat xOffset = -borderThickness * 1.0f * chessboardSize;
GLfloat yOffset = -borderThickness * 1.0f * chessboardSize;
GLfloat width = (chessboardSize + 2 * borderThickness);
GLfloat height = (chessboardSize + 2 * borderThickness);
GLfloat zPos = 5.0f;

void Border::drawGeometry() {

    // Draw the border using OpenGL rectangles
    glBegin(GL_QUADS);

    // Top border
    glColor3f(0.55f, 0.87f, 0.44f);
    glVertex3f(xOffset, yOffset, zPos);
    glVertex3f(xOffset + width, yOffset, zPos);
    glVertex3f(xOffset + width, yOffset + borderThickness, zPos);
    glVertex3f(xOffset, yOffset + borderThickness, zPos);

    // Bottom border
    glColor3f(0.9f, 0.25f, 0.25f);
    glVertex3f(xOffset, yOffset + height - borderThickness, zPos);
    glVertex3f(xOffset + width, yOffset + height - borderThickness, zPos);
    glVertex3f(xOffset + width, yOffset + height, zPos);
    glVertex3f(xOffset, yOffset + height, zPos);



    // Left border
    glColor3f(0.4f, 0.8f, 0.8f);
    glVertex3f(xOffset, yOffset + borderThickness, zPos);
    glVertex3f(xOffset + borderThickness, yOffset + borderThickness, zPos);
    glVertex3f(xOffset + borderThickness, yOffset + height - borderThickness, zPos);
    glVertex3f(xOffset, yOffset + height - borderThickness, zPos);


    // Right border
    glColor3f(0.68f, 0.4f, 0.8f);
    glVertex3f(xOffset + width - borderThickness, yOffset + borderThickness, zPos);
    glVertex3f(xOffset + width, yOffset + borderThickness, zPos);
    glVertex3f(xOffset + width, yOffset + height - borderThickness, zPos);
    glVertex3f(xOffset + width - borderThickness, yOffset + height - borderThickness, zPos);

    glEnd();
}
