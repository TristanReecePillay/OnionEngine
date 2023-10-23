// SquareAnim.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <ctime>
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
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
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
void updateAnimation();

TextureManager* textureManager;
GameObject* gameObject;
TerrainGameObject* terrain; 
Chessboard* chessboard;
Border* border;
Rook* rook;
Knight* knight;
Pawn* pawn;
King* king;
Queen* queen;
Bishop* bishop;

glm::vec3 cameraPositions[3] = {
    glm::vec3(0.0f, 10.0f, -20.0f),  // Camera 1 position
    glm::vec3(20.0f, 10.0f, 0.0f),  // Camera 2 position
    glm::vec3(0.1f, 40.0f, 0.0f) // Camera 3 position
};


int currentCamera = 0; // Index of the currently active camera
bool isAnimating = false;
float animationDuration = 2.0f; // Animation duration in seconds
float animationStartTime = 0.0f;
glm::vec3 targetRookPosition;
glm::vec3 targetKnightPosition;

#include <vector>

// Store the original and current positions of the chess pieces
std::vector<glm::vec3> originalRookPositions; 
std::vector<glm::vec3> originalKnightPositions; 
std::vector<glm::vec3> currentRookPositions; 
std::vector<glm::vec3> currentKnightPositions; 

void interpolatePiecePositions() {
    if (isAnimating) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - animationStartTime;
        if (elapsedTime < animationDuration) {
            float t = elapsedTime / animationDuration;
            // Interpolate the position of the rook
            for (size_t i = 0; i < originalRookPositions.size(); i++) {
                currentRookPositions[i] = glm::mix(originalRookPositions[i], targetRookPosition, t);
            }

            for (size_t i = 0; i < originalKnightPositions.size(); i++) {
                currentKnightPositions[i] = glm::mix(originalKnightPositions[i], targetKnightPosition, t);
            }
        }
        else {
            isAnimating = false;
        }
    }
}

void resetPiecePositions() {
    isAnimating = false;
    for (size_t i = 0; i < originalRookPositions.size(); i++) {
        currentRookPositions[i] = originalRookPositions[i];
    }
    for (size_t i = 0; i < originalKnightPositions.size(); i++) {
        currentKnightPositions[i] = originalKnightPositions[i];
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
    gameObject->setPosition(0, 0, 0);

    chessboard = new Chessboard();
    chessboard->generateDisplayList();

    border = new Border();
    border->generateDisplayList();

    rook = new Rook();
    rook->generateDisplayList();

    knight = new Knight();
    knight->generateDisplayList();

    pawn = new Pawn();
    pawn->generateDisplayList();

    king = new King();
    king->generateDisplayList();

    queen = new Queen();
    queen->generateDisplayList();

    //bishop = new Bishop();
    //bishop->generateDisplayList();

    // Initialize positions for the initial chess pieces
    originalRookPositions.push_back(glm::vec3(-6.0f, 1.0f, 6.0f));
    originalKnightPositions.push_back(glm::vec3(-6.0f, 1.0f, -6.0f));

    currentRookPositions = originalRookPositions;
    currentKnightPositions = originalKnightPositions;

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
    delete rook;
    delete knight;
    delete pawn;
    delete king;
    delete queen;
    delete bishop;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    interpolatePiecePositions();
    updateAnimation();

    // Set the camera view based on the currently active camera
    glm::vec3 cameraPosition = cameraPositions[currentCamera];
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Target point

    gluLookAt(
        cameraPosition.x, cameraPosition.y, cameraPosition.z,
        cameraTarget.x, cameraTarget.y, cameraTarget.z,
        0.0, 1.0, 0.0
    );

    for (size_t i = 0; i < originalRookPositions.size(); i++) {
        //Black Pieces
        glPushMatrix(); {

            textureManager->useTexture("darkMarble");
            glColor3f(0.2f, 0.2f, 0.2f);
            glTranslatef(currentRookPositions[i].x, currentRookPositions[i].y, currentRookPositions[i].z);
            rook->draw();
        }
        glPopMatrix();
    }


    glPushMatrix(); {
        glColor3f(0.2f, 0.2f, 0.2f);
        glTranslatef(-6.0f, 1.0f, -8.0f);
        rook->draw();
    }
    glPopMatrix();

    for (size_t i = 0; i < originalKnightPositions.size(); i++) {
        glPushMatrix(); {
            glColor3f(0.2f, 0.2f, 0.2f);
            glTranslatef(currentKnightPositions[i].x, currentKnightPositions[i].y, currentKnightPositions[i].z); 
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            knight->draw();
        }
        glPopMatrix();
    }


    glPushMatrix(); {
        glColor3f(0.2f, 0.2f, 0.2f);
        glTranslatef(-6.0f, 1.0f, 4.0f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        knight->draw();
    }
    glPopMatrix();

    //White pieces
    glPushMatrix(); {
        textureManager->useTexture("marble");
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, 6.0f);
        rook->draw();
    }
    glPopMatrix();

    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, -8.0f);
        rook->draw();
    }
    glPopMatrix();

    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, -6.0f);
        knight->draw();
    }
    glPopMatrix();

    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, 4.0f);
        knight->draw();
    }
    glPopMatrix();

  
    textureManager->useTexture("grass");

    glPushMatrix(); {
       
        terrain->draw();
    }
    glPopMatrix();

    glPushMatrix(); {

        textureManager->useTexture("pink");
        glRotatef(-90, 1, 0, 0);
        glScalef(2.0f, 2.0f, 1.0f);
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
        case 'r':
            // Add a new rook at a random position
            originalRookPositions.push_back(glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5));
            currentRookPositions.push_back(originalRookPositions.back());
            break;
        case 'k':
            // Add a new knight at a random position
            originalKnightPositions.push_back(glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5));
            currentKnightPositions.push_back(originalKnightPositions.back());
            break;
        case ' ':
            if (!isAnimating) {
                // Start the animation
                targetRookPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetKnightPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5); 
                animationStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                isAnimating = true;
            }
            break;
        case 'x':
            resetPiecePositions();
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

void updateAnimation() {
    // This function should update the targetRookPosition if you're animating the rook's movement.
    //  set the new target position based on some logic.
    // For example, if you want the rook to move to a random position, you can do something like this:

    if (isAnimating) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - animationStartTime;

        if (elapsedTime >= animationDuration) {
            // Animation is complete, set a new target position.
            targetRookPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetKnightPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            animationStartTime = currentTime; // Reset animation start time
        }
    }
}





