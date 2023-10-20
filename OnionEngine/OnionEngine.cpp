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
#include "Chessboard.h"
#include "Border.h"
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


void init();
void display();
void timer(int);
void initGameObjects();
void cleanUp();
void keyCallback(unsigned char key, int x, int y); // Added key callback to switch camera positions
void specialKeyCallback(int key, int x, int y);

TextureManager* textureManager;
GameObject* gameObject;
TerrainGameObject* terrain; 
Chessboard* chessboard;
Border* border;

glm::vec3 cameraPositions[3] = {
    glm::vec3(20.0f, 20.0f, -10.0f),  // Camera 0 position
    glm::vec3(50.0f, 20.0f, 0.0f),  // Camera 1 position
    glm::vec3(50.0f, 50.0f, 50.0f) // Camera 2 position
};

int currentCamera = 0; // Index of the currently active camera
 

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    int windowX = (int)(glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2;
    int windowY = (int)(glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2;

    glutInitWindowPosition(windowX, windowY);
    glutInitWindowSize(WIDTH, HEIGHT);
    int window = glutCreateWindow("Terrain Renderer");
  
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
    textureManager = new TextureManager();

    gameObject = new GameObject();
    gameObject->setPosition(1, 0, 0);

    chessboard = new Chessboard();
    chessboard->generateDisplayList();

    border = new Border();
    border->generateDisplayList();

    //creates terrain
    terrain = new TerrainGameObject(textureManager->getTexture("heightmap"), 50, 5);
    terrain->generateDisplayList();
}

void cleanUp() {
    delete textureManager;
    delete gameObject;
    delete terrain;
    delete chessboard;
    delete border;
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
        glRotatef(-90, 1, 0, 0);
        chessboard->draw();
        border->draw();
    }
    glPopMatrix();

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




