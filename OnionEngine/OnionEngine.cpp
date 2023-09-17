// SquareAnim.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <cmath>
#include "GameObject.h"
#include "TextureManager.h"
#include "TexturedCube.h"
#include "Terrain.h"
#include "Shader.h"
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
const int chessboardSize = 8; // Adjust the size according to your desired chessboard size
const GLfloat minHeightOffset = -0.1f; // Adjust the minimum height offset as needed
const GLfloat maxHeightOffset = 0.1f;  // Adjust the maximum height offset as needed


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
TexturedCube* texturedCube; 

glm::vec3 cameraPositions[3] = {
    glm::vec3(0.0f, 0.0f, 5.0f),  // Camera 0 position
    glm::vec3(5.0f, -5.0f, 0.0f),  // Camera 1 position
    glm::vec3(-5.0f, 0.0f, 0.0f) // Camera 2 position
};

int currentCamera = 0; // Index of the currently active camera
// Create the Shader object
//Shader shader("vertex_shader.vert.glsl", "fragment_shader.glsl"); 
//Terrain terrain("../Textures/HeightMap2.png"); 

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
    const GLfloat borderWidth = 0.0f; // NOPE this is the space between cells

    // Chessboard square colors 
    const glm::vec3 blackSquareColor(0.0f, 0.0f, 0.0f);
    const glm::vec3 whiteSquareColor(1.0f, 1.0f, 1.0f);
    const glm::vec3 borderColor(0.2f, 0.2f, 0.2f); // Gray border color

    // Calculate square height randomization range
    const GLfloat minHeightOffset = -0.05f; // Minimum height offset
    const GLfloat maxHeightOffset = 0.05f;  // Maximum height offset

    for (int row = 0; row < chessboardSize; row++) {
        for (int col = 0; col < chessboardSize; col++) {
            // Calculate position for each square
           // GLfloat xPos = static_cast<GLfloat>(col) * (cellSize + borderWidth); //- 4.0f;
           // GLfloat yPos = static_cast<GLfloat>(row) * (cellSize + borderWidth); //- 4.0f;
           // GLfloat zPos = 0.0f; // Chessboard is at a height of 0.5 units
            GLfloat xPos = static_cast<GLfloat>(col) * (cellSize + borderWidth);
            GLfloat yPos = static_cast<GLfloat>(row) * (cellSize + borderWidth);
            GLfloat zPos = squareHeights[row][col];

            // Determine the square color based on row and column
            glm::vec3 squareColor = ((row + col) % 2 == 0) ? blackSquareColor : whiteSquareColor;

            // Applying the offsets to each square
           // GLfloat xOffset = (static_cast<GLfloat>(rand()) / RAND_MAX) * (maxHeightOffset - minHeightOffset) + minHeightOffset;
          //  GLfloat yOffset = (static_cast<GLfloat>(rand()) / RAND_MAX) * (maxHeightOffset - minHeightOffset) + minHeightOffset;

            // Apply the height offset
          //  zPos += xOffset + yOffset;
          
            // Begin immediate mode rendering
            glBegin(GL_QUADS);

            // Define vertices and colors for the square
            glColor3f(squareColor.r, squareColor.g, squareColor.b);
            glVertex3f(xPos, yPos, zPos);
            glVertex3f(xPos + cellSize, yPos, zPos);
            glVertex3f(xPos + cellSize, yPos + cellSize, zPos);
            glVertex3f(xPos, yPos + cellSize, zPos);

            // End immediate mode rendering for the square
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
    glutCreateWindow("Terrain Renderer");

   

    //// Define and initialize model, view, and projection matrices
    //glm::mat4 modelMatrix = glm::mat4(1.0f); // Initialize as an identity matrix  
    //glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Example view matrix  
    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 1.0f, 1000.0f); // Example projection matrix  

    //// Set shader uniforms for model, view, and projection matrices
    //shader.use(); 
    //shader.setMat4("model", modelMatrix);  
    //shader.setMat4("view", viewMatrix); 
    //shader.setMat4("projection", projectionMatrix); 
    //shader.unuse();
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

    gluLookAt(
        0.0, 0.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glClearColor(0.6f, 0.8f, 0.9f, 1.0f);

    initGameObjects();
}

void initGameObjects() {
    textureManager = new TextureManager();
    texturedCube = new TexturedCube();
    texturedCube->generateDisplayList();

    //delete textureManager;
    //delete texturedCube;

    // Create the terrain object
    //terrain.setupMesh();  
}

void cleanUp() {
    delete textureManager;
    delete gameObject;
    delete texturedCube;
}





/*
void generateChessboard() {


    // size of the chessboard (8x8 squares)
    int chessboardSize = 8;
    GLfloat squareSize = 1.0f;
    GLfloat borderWidth = 0.5f;
    GLfloat squareHeight = 0.5f; // Chessboard height

    for (int row = 0; row < chessboardSize; row++) {
        for (int col = 0; col < chessboardSize; col++) {
            GLfloat xPos = static_cast<GLfloat>(col) * (squareSize + borderWidth) - chessboardSize * (squareSize + borderWidth) / 2.0f;
            GLfloat yPos = static_cast<GLfloat>(row) * (squareSize + borderWidth) - chessboardSize * (squareSize + borderWidth) / 2.0f;

            // Offsets
            GLfloat xOffset = (static_cast<GLfloat>(rand()) / RAND_MAX - 0.5f) * squareHeight;
            GLfloat yOffset = (static_cast<GLfloat>(rand()) / RAND_MAX - 0.5f) * squareHeight;
            GLfloat zOffset = (static_cast<GLfloat>(rand()) / RAND_MAX - 0.5f) * squareHeight;

            //...
        }
    }
}*/


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

    glRotatef(45, 1, 1, 0);
    textureManager->useTexture("map");
    texturedCube->draw();

    // Renders the chessboard here
    generateChessboard(); // Calling the function that renders the chessboard

    // Render the terrain
    //terrain.render(glm::mat4(1.0f), glm::mat4(1.0f));

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




