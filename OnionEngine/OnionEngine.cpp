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

void init();
void display();
void timer(int);
void initGameObjects();
void cleanUp();
void keyCallback(unsigned char key, int x, int y); // Added key callback to switch camera positions
void specialKeyCallback(int key, int x, int y);

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



