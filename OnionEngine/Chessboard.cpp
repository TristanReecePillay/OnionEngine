#include "Chessboard.h"
#include <iostream>
#include <GL/freeglut.h>

//Updated 

    // Define chessboard dimensions
const int chessboardSize = 8; // 8x8 grid
const GLfloat cellSize = 1.0f; // Each cell is 1x1 units
const GLfloat borderWidth = 0.0f; // NOPE this is the space between cells which we need at zero
const GLfloat cellDepth = 0.5f;

// Chessboard square colors 
const glm::vec3 blackSquareColor(0.0f, 0.0f, 0.0f);
const glm::vec3 whiteSquareColor(1.0f, 1.0f, 1.0f);
const glm::vec3 borderColor(0.2f, 0.2f, 0.2f); // Gray border color

// Calculate square height randomization range
const GLfloat minHeightOffset = 0.00f; // Minimum height offset
const GLfloat maxHeightOffset = 0.05f;  // Maximum height offset


void Chessboard::drawGeometry() {

    for (int row = 0; row < chessboardSize; row++) {
        for (int col = 0; col < chessboardSize; col++) {

            GLfloat xPos = static_cast<GLfloat>(col) * (cellSize + borderWidth) - (chessboardSize - 1) * 0.5f * (cellSize + borderWidth);
            GLfloat yPos = static_cast<GLfloat>(row) * (cellSize + borderWidth) - (chessboardSize - 1) * 0.5f * (cellSize + borderWidth);
            GLfloat zPos = 5.0f; //squareHeights[row][col];

            // Determine the square color based on row and column
            glm::vec3 squareColor = ((row + col) % 2 == 0) ? blackSquareColor : whiteSquareColor;


            // Begin immediate mode rendering
            glBegin(GL_QUADS);

            // Define vertices and colors for the top face
            glColor3f(squareColor.r, squareColor.g, squareColor.b);
            glVertex3f(xPos, yPos, zPos);
            glVertex3f(xPos + cellSize, yPos, zPos);
            glVertex3f(xPos + cellSize, yPos + cellSize, zPos);
            glVertex3f(xPos, yPos + cellSize, zPos);

            // Define vertices and colors for the bottom face (same as top face but lowered)
            glVertex3f(xPos, yPos, zPos - cellDepth);
            glVertex3f(xPos + cellSize, yPos, zPos - cellDepth);
            glVertex3f(xPos + cellSize, yPos + cellSize, zPos - cellDepth);
            glVertex3f(xPos, yPos + cellSize, zPos - cellDepth);

            // Define vertices and colors for the front face (sides of the cell)
            glVertex3f(xPos, yPos, zPos);
            glVertex3f(xPos + cellSize, yPos, zPos);
            glVertex3f(xPos + cellSize, yPos, zPos - cellDepth);
            glVertex3f(xPos, yPos, zPos - cellDepth);

            // Define vertices and colors for the right face (sides of the cell)
            glVertex3f(xPos + cellSize, yPos, zPos);
            glVertex3f(xPos + cellSize, yPos + cellSize, zPos);
            glVertex3f(xPos + cellSize, yPos + cellSize, zPos - cellDepth);
            glVertex3f(xPos + cellSize, yPos, zPos - cellDepth);

            // Define vertices and colors for the back face (sides of the cell)
            glVertex3f(xPos, yPos + cellSize, zPos);
            glVertex3f(xPos + cellSize, yPos + cellSize, zPos);
            glVertex3f(xPos + cellSize, yPos + cellSize, zPos - cellDepth);
            glVertex3f(xPos, yPos + cellSize, zPos - cellDepth);

            // Define vertices and colors for the left face (sides of the cell)
            glVertex3f(xPos, yPos, zPos);
            glVertex3f(xPos, yPos + cellSize, zPos);
            glVertex3f(xPos, yPos + cellSize, zPos - cellDepth);
            glVertex3f(xPos, yPos, zPos - cellDepth);

            glEnd();
        }
    }
}
