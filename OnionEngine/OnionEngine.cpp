// SquareAnim.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "Terrain.h"
#include "Shader.h"
#include "GameObject.h"
#include "Settings.h"
#include "TextureManager.h"
#include "TerrainGameObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 
#define GLEW_STATIC

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


const int WIDTH = 800;
const int HEIGHT = 600;
const int chessboardSize = 8; // the standard size 
const GLfloat minHeightOffset = -0.1f; // the minimum height offset as needed
const GLfloat maxHeightOffset = 0.1f;  // the maximum height offset as needed
const GLfloat cellDepth = 0.5f; // Adjust as needed for the depth of the cells

void init();
void display();
void timer(int);
void initGameObjects();
void cleanUp();
void keyCallback(unsigned char key, int x, int y); // Added key callback to switch camera positions
void specialKeyCallback(int key, int x, int y);
void generateChessboard();


TextureManager* textureManager;
GameObject* gameObject;
TerrainGameObject* terrain; 

glm::vec3 cameraPositions[3] = {
    glm::vec3(20.0f, 20.0f, -10.0f),  // Camera 0 position
    glm::vec3(50.0f, -50.0f, 0.0f),  // Camera 1 position
    glm::vec3(50.0f, 50.0f, 0.0f) // Camera 2 position
};

int currentCamera = 0; // Index of the currently active camera
 
// Defining a 2D vector to store the height offsets for each square SO that it doesnt render every frame 
//and look jittery 
std::vector<std::vector<GLfloat>> squareHeights(chessboardSize, std::vector<GLfloat>(chessboardSize, 0.0f)); 

void initializeChessboard() {
    // Calculate and store random height offsets for each square
    for (int row = 0; row < chessboardSize; row++) {
        for (int col = 0; col < chessboardSize; col++) {
            GLfloat xOffset = (static_cast<GLfloat>(rand()) / RAND_MAX) * (maxHeightOffset - minHeightOffset) + minHeightOffset;
            GLfloat yOffset = (static_cast<GLfloat>(rand()) / RAND_MAX) * (maxHeightOffset - minHeightOffset) + minHeightOffset;

            squareHeights[row][col] = xOffset + yOffset;
        }
    }
}


void generateChessboard() {
    //Updated 

    // Define chessboard dimensions
    const int chessboardSize = 8; // 8x8 grid
    const GLfloat cellSize = 1.0f; // Each cell is 1x1 units
    const GLfloat borderWidth = 0.0f; // NOPE this is the space between cells which we need at zero

    // Chessboard square colors 
    const glm::vec3 blackSquareColor(0.0f, 0.0f, 0.0f);
    const glm::vec3 whiteSquareColor(1.0f, 1.0f, 1.0f);
    const glm::vec3 borderColor(0.2f, 0.2f, 0.2f); // Gray border color

    // Calculate square height randomization range
    const GLfloat minHeightOffset = 0.00f; // Minimum height offset
    const GLfloat maxHeightOffset = 0.05f;  // Maximum height offset


    for (int row = 0; row < chessboardSize; row++) {
        for (int col = 0; col < chessboardSize; col++) {

            GLfloat xPos = static_cast<GLfloat>(col) * (cellSize + borderWidth) - (chessboardSize - 1) * 0.5f * (cellSize + borderWidth); 
            GLfloat yPos = static_cast<GLfloat>(row) * (cellSize + borderWidth) - (chessboardSize - 1) * 0.5f * (cellSize + borderWidth); 
            GLfloat zPos = squareHeights[row][col];

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

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    int windowX = (int)(glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2;
    int windowY = (int)(glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2;

    glutInitWindowPosition(windowX, windowY);
    glutInitWindowSize(WIDTH, HEIGHT);
    int window = glutCreateWindow("Terrain Renderer");

    // Initialize GLEW
    /*GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(glewInitResult) << std::endl;
        glutDestroyWindow(window);
        return -1;
    }*/
  

    // Initialize the chessboard with random height offsets
    initializeChessboard();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyCallback); // Register the key callback
    glutSpecialFunc(specialKeyCallback);
    
    init();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glutMainLoop();
    
    cleanUp();

    return 0;
}


void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(50.0, (double)WIDTH / (double)HEIGHT, 1.0, 1000.0);

    glClearColor(0.6f, 0.8f, 0.9f, 1.0f); //(0.6f, 0.8f, 0.9f, 1.0f) For light blue

    initGameObjects();
}

void initGameObjects() {
 
    //Create the terrain object
    //terrain.setupMesh();
    textureManager = new TextureManager();

    gameObject = new GameObject();
    gameObject->setPosition(1, 0, 0);

    //creates terrain
    terrain = new TerrainGameObject(textureManager->getTexture("heightmap"), 50, 5);
    terrain->generateDisplayList();


}

void cleanUp() {
    delete textureManager;
    delete gameObject;
    delete terrain;
}


void drawBorder() {
    // Set the color for the border
    glColor3f(0.6f, 0.8f, 0.2f); // Color of border
    //0.5f, 0.2f, 0.0f //brown
    //0.8f, 0.6f, 0.0f //Mustard
    //0.6f, 0.8f, 0.2f// Best Color : Green

    // Calculate the positions and dimensions for the border rectangles
    GLfloat borderThickness = 0.5f; // Changes border thickness //1 looks better but because of the brief
    GLfloat chessboardSize = 8.0f; // Changes the chessboard size
    GLfloat xOffset = -borderThickness * 1.0f * chessboardSize;
    GLfloat yOffset = -borderThickness * 1.0f * chessboardSize;
    GLfloat width = (chessboardSize + 2 * borderThickness);
    GLfloat height = (chessboardSize + 2 * borderThickness);

    // Draw the border using OpenGL rectangles
    glBegin(GL_QUADS);

    // Top border
    glVertex3f(xOffset, yOffset, 0.0f);
    glVertex3f(xOffset + width, yOffset, 0.0f);
    glVertex3f(xOffset + width, yOffset + borderThickness, 0.0f);
    glVertex3f(xOffset, yOffset + borderThickness, 0.0f);

    // Bottom border
    glVertex3f(xOffset, yOffset + height - borderThickness, 0.0f);
    glVertex3f(xOffset + width, yOffset + height - borderThickness, 0.0f);
    glVertex3f(xOffset + width, yOffset + height, 0.0f);
    glVertex3f(xOffset, yOffset + height, 0.0f);

    // Left border
    glVertex3f(xOffset, yOffset + borderThickness, 0.0f);
    glVertex3f(xOffset + borderThickness, yOffset + borderThickness, 0.0f);
    glVertex3f(xOffset + borderThickness, yOffset + height - borderThickness, 0.0f);
    glVertex3f(xOffset, yOffset + height - borderThickness, 0.0f);

    // Right border
    glVertex3f(xOffset + width - borderThickness, yOffset + borderThickness, 0.0f);
    glVertex3f(xOffset + width, yOffset + borderThickness, 0.0f);
    glVertex3f(xOffset + width, yOffset + height - borderThickness, 0.0f);
    glVertex3f(xOffset + width - borderThickness, yOffset + height - borderThickness, 0.0f);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the camera view based on the currently active camera
    glm::vec3 cameraPosition = cameraPositions[currentCamera];
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Target point

    gluLookAt(
        cameraPosition.x, cameraPosition.y, cameraPosition.z,
        cameraTarget.x, cameraTarget.y, cameraTarget.z,
        0.0, 1.0, 0.0
    );

    glPushMatrix(); {
        terrain->draw();
    }
    glPopMatrix();
  
    glRotatef(-90, 1, 0, 0);

    // Draw the border
    drawBorder();
    // Renders the chessboard here
    generateChessboard(); // Calling the function that renders the chessboard

    glutSwapBuffers();
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void keyCallback(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        currentCamera = 0; // Switch to camera 0
        break;
    case '2':
        currentCamera = 1; // Switch to camera 1
        break;
    case '3':
        currentCamera = 2; // Switch to camera 2
        break;
    case 27: // ESC key
        exit(0); // Exit the program
        break;
    }
    glutPostRedisplay();
}

void specialKeyCallback(int key, int x, int y) {
    // Handle arrow key presses to navigate between cameras
    switch (key) {
    case GLUT_KEY_LEFT:
        currentCamera = (currentCamera + 2) % 3; // Switch to the previous camera
        break;
    case GLUT_KEY_RIGHT:
        currentCamera = (currentCamera + 1) % 3; // Switch to the next camera
        break;
    }
    glutPostRedisplay();
}




