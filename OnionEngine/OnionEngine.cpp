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
#include "Model.h"
#include "ModelPart.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 
#define GLEW_STATIC 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

//Tinyobjloader
#define TINYOBJLOADER_IMPLEMENTATION
#include<tiny_obj_loader.h>

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
Model* catModel;

glm::vec3 cameraPositions[3] = {
    glm::vec3(0.0f, 15.0f, -30.0f),  // Camera 1 position
    glm::vec3(20.0f, 20.0f, 0.0f),  // Camera 2 position
    glm::vec3(0.1f, 40.0f, 0.0f) // Camera 3 position
};


int currentCamera = 0; // Index of the currently active camera
bool isAnimating = false;
float animationDuration = 2.0f; // Animation duration in seconds
float animationStartTime = 0.0f;
glm::vec3 targetBlackRookOnePosition;
glm::vec3 targetBlackRookTwoPosition;
glm::vec3 targetBlackKnightOnePosition;
glm::vec3 targetBlackKnightTwoPosition;
glm::vec3 targetBlackPawnPosition;

glm::vec3 targetWhiteRookOnePosition;
glm::vec3 targetWhiteRookTwoPosition;
glm::vec3 targetWhiteKnightOnePosition;
glm::vec3 targetWhiteKnightTwoPosition;
glm::vec3 targetWhitePawnPosition;

#include <vector>

// Store the original and current positions of the chess pieces
std::vector<glm::vec3> originalBlackRookOnePositions; 
std::vector<glm::vec3> originalBlackKnightOnePositions;
std::vector<glm::vec3> originalBlackRookTwoPositions;
std::vector<glm::vec3> originalBlackKnightTwoPositions;
std::vector<glm::vec3> originalBlackPawnPositions;

std::vector<glm::vec3> currentBlackRookOnePositions; 
std::vector<glm::vec3> currentBlackKnightOnePositions;
std::vector<glm::vec3> currentBlackRookTwoPositions;
std::vector<glm::vec3> currentBlackKnightTwoPositions;
std::vector<glm::vec3> currentBlackPawnPositions;


std::vector<glm::vec3> originalWhiteRookOnePositions;
std::vector<glm::vec3> originalWhiteRookTwoPositions;
std::vector<glm::vec3> originalWhiteKnightOnePositions;
std::vector<glm::vec3> originalWhiteKnightTwoPositions;
std::vector<glm::vec3> originalWhitePawnPositions;

std::vector<glm::vec3> currentWhiteRookOnePositions;
std::vector<glm::vec3> currentWhiteRookTwoPositions;
std::vector<glm::vec3> currentWhiteKnightOnePositions;
std::vector<glm::vec3> currentWhiteKnightTwoPositions;
std::vector<glm::vec3> currentWhitePawnPositions;


void interpolatePiecePositions() {
    if (isAnimating) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - animationStartTime;
        if (elapsedTime < animationDuration) {
            float t = elapsedTime / animationDuration;
            // Interpolate the position of the rook
            for (size_t i = 0; i < originalBlackRookOnePositions.size(); i++) {
                currentBlackRookOnePositions[i] = glm::mix(originalBlackRookOnePositions[i], targetBlackRookOnePosition, t);
            }

            for (size_t i = 0; i < originalBlackRookTwoPositions.size(); i++) {
                currentBlackRookTwoPositions[i] = glm::mix(originalBlackRookTwoPositions[i], targetBlackRookTwoPosition, t);
            }

            for (size_t i = 0; i < originalBlackKnightOnePositions.size(); i++) {
                currentBlackKnightOnePositions[i] = glm::mix(originalBlackKnightOnePositions[i], targetBlackKnightOnePosition, t);
            }

            for (size_t i = 0; i < originalBlackKnightTwoPositions.size(); i++) {
                currentBlackKnightTwoPositions[i] = glm::mix(originalBlackKnightTwoPositions[i], targetBlackKnightTwoPosition, t);
            }

            for (size_t i = 0; i < originalBlackPawnPositions.size(); i++) {
                currentBlackPawnPositions[i] = glm::mix(originalBlackPawnPositions[i], targetBlackPawnPosition, t);
            }



            for (size_t i = 0; i < originalWhiteRookOnePositions.size(); i++) {
                currentWhiteRookOnePositions[i] = glm::mix(originalWhiteRookOnePositions[i], targetWhiteRookOnePosition, t);
            }

            for (size_t i = 0; i < originalWhiteRookTwoPositions.size(); i++) {
                currentWhiteRookTwoPositions[i] = glm::mix(originalWhiteRookTwoPositions[i], targetWhiteRookTwoPosition, t);
            }

            for (size_t i = 0; i < originalWhiteKnightOnePositions.size(); i++) {
                currentWhiteKnightOnePositions[i] = glm::mix(originalWhiteKnightOnePositions[i], targetWhiteKnightOnePosition, t);
            }

            for (size_t i = 0; i < originalWhiteKnightTwoPositions.size(); i++) {
                currentWhiteKnightTwoPositions[i] = glm::mix(originalWhiteKnightTwoPositions[i], targetWhiteKnightTwoPosition, t);
            }
            for (size_t i = 0; i < originalWhitePawnPositions.size(); i++) {
                currentWhitePawnPositions[i] = glm::mix(originalWhitePawnPositions[i], targetWhitePawnPosition, t);
            }

        }
        else {
            isAnimating = false;
        }
    }
}

void resetPiecePositions() {
    isAnimating = false;
    for (size_t i = 0; i < originalBlackRookOnePositions.size(); i++) {
        currentBlackRookOnePositions[i] = originalBlackRookOnePositions[i];
    }
    for (size_t i = 0; i < originalBlackRookTwoPositions.size(); i++) {
        currentBlackRookTwoPositions[i] = originalBlackRookTwoPositions[i];
    }
    for (size_t i = 0; i < originalBlackKnightOnePositions.size(); i++) {
        currentBlackKnightOnePositions[i] = originalBlackKnightOnePositions[i];
    }
    for (size_t i = 0; i < originalBlackKnightTwoPositions.size(); i++) {
        currentBlackKnightTwoPositions[i] = originalBlackKnightTwoPositions[i];
    }
    for (size_t i = 0; i < originalBlackPawnPositions.size(); i++) {
        currentBlackPawnPositions[i] = originalBlackPawnPositions[i];
    }

    for (size_t i = 0; i < originalWhiteRookOnePositions.size(); i++) {
        currentWhiteRookOnePositions[i] = originalWhiteRookOnePositions[i];
    }
    for (size_t i = 0; i < originalWhiteRookTwoPositions.size(); i++) {
        currentWhiteRookTwoPositions[i] = originalWhiteRookTwoPositions[i];
    }
    for (size_t i = 0; i < originalWhiteKnightOnePositions.size(); i++) {
        currentWhiteKnightOnePositions[i] = originalWhiteKnightOnePositions[i];
    }
    for (size_t i = 0; i < originalWhiteKnightTwoPositions.size(); i++) {
        currentWhiteKnightTwoPositions[i] = originalWhiteKnightTwoPositions[i];
    }
    for (size_t i = 0; i < originalWhitePawnPositions.size(); i++) {
        currentWhitePawnPositions[i] = originalWhitePawnPositions[i];
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
  
    glutMotionFunc(Input::mousePositionUpdate); 
    glutPassiveMotionFunc(Input::mousePositionUpdate); 
    glutKeyboardFunc(Input::keyboardUpdate); 
    glutKeyboardUpFunc(Input::keyboardUpUpdate); 

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

    bishop = new Bishop();
    bishop->generateDisplayList();

    catModel = new Model("../Models/cat1/", "cat1"); 
    catModel->generateDisplayList(); 

    // Initialize positions for the initial chess pieces
    originalBlackRookOnePositions.push_back(glm::vec3(-6.0f, 1.0f, 6.0f));  // x ltor y zfrontnbsack 
    originalBlackRookTwoPositions.push_back(glm::vec3(-6.0f, 1.0f, -8.0f));
    originalBlackKnightOnePositions.push_back(glm::vec3(-6.0f, 1.0f, -6.0f)); //refs
    originalBlackKnightTwoPositions.push_back(glm::vec3(-6.0f, 1.0f, 4.0f));
    originalBlackPawnPositions.push_back(glm::vec3(-4.0f, 1.0f, 6.0f));

    originalWhiteRookOnePositions.push_back(glm::vec3(8.0f, 1.0f, 6.0f));
    originalWhiteRookTwoPositions.push_back(glm::vec3(8.0f, 1.0f, -8.0f));
    originalWhiteKnightOnePositions.push_back(glm::vec3(8.0f, 1.0f, -6.0f));
    originalWhiteKnightTwoPositions.push_back(glm::vec3(8.0f, 1.0f, 4.0f));
    originalWhitePawnPositions.push_back(glm::vec3(6.0f, 1.0f, 6.0f));

    currentBlackRookOnePositions = originalBlackRookOnePositions;
    currentBlackRookTwoPositions = originalBlackRookTwoPositions;
    currentBlackKnightOnePositions = originalBlackKnightOnePositions;
    currentBlackKnightTwoPositions = originalBlackKnightTwoPositions;
    currentBlackPawnPositions = originalBlackPawnPositions;

    currentWhiteRookOnePositions = originalWhiteRookOnePositions;
    currentWhiteRookTwoPositions = originalWhiteRookTwoPositions;
    currentWhiteKnightOnePositions = originalWhiteKnightOnePositions;
    currentWhiteKnightTwoPositions = originalWhiteKnightTwoPositions;
    currentWhitePawnPositions = originalWhitePawnPositions;

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
    delete catModel;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Input::updateBefore(); 

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

    //CAT MODEL
    glPushMatrix(); {
        //glRotatef(90.0, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 10.0f, 0.0f);
        catModel->draw();
    }
    glPopMatrix();

    //BLACK PIECES
   textureManager->useTexture("darkMarble");
    for (size_t i = 0; i < originalBlackRookOnePositions.size(); i++) {
        //Black Rook 1
        glPushMatrix(); {
            glColor3f(0.5f, 0.5f, 0.5f); 
            glTranslatef(currentBlackRookOnePositions[i].x, currentBlackRookOnePositions[i].y, currentBlackRookOnePositions[i].z);
            rook->draw();
        }
        glPopMatrix();
    }

    for (size_t i = 0; i < originalBlackRookTwoPositions.size(); i++) {
        textureManager->useTexture("darkMarble");
        //Black Rook 2
        glPushMatrix(); {
            glColor3f(0.5f, 0.5f, 0.5f);
            glTranslatef(currentBlackRookTwoPositions[i].x, currentBlackRookTwoPositions[i].y, currentBlackRookTwoPositions[i].z);
            rook->draw();
        }
        glPopMatrix(); 
    }

   

    for (size_t i = 0; i < originalBlackKnightOnePositions.size(); i++) {
        //Black Knight 1
        textureManager->useTexture("darkMarble");
        glPushMatrix(); {//draw
            glColor3f(0.5f, 0.5f, 0.5f);
            glTranslatef(currentBlackKnightOnePositions[i].x, currentBlackKnightOnePositions[i].y, currentBlackKnightOnePositions[i].z); //draw end
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            knight->draw();
        }
        glPopMatrix();
    }

    for (size_t i = 0; i < originalBlackKnightTwoPositions.size(); i++) {
        textureManager->useTexture("darkMarble");
        //Black Knight 2
        glPushMatrix(); {
            glColor3f(0.5f, 0.5f, 0.5f);
            glTranslatef(currentBlackKnightTwoPositions[i].x, currentBlackKnightTwoPositions[i].y, currentBlackKnightTwoPositions[i].z);
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            knight->draw();
        }
        glPopMatrix();
    }
    
    //Black King
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(0.8f, 0.08f, 0.08f);
        glTranslatef(-6.0f, 1.0f, 0.0f);
        king->draw();
    }
    glPopMatrix(); 


    //Black Bishop 1 
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-6.0f, 1.0f, 2.0f);
        bishop->draw();
    }
    glPopMatrix();

    //Black Bishop 2
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-6.0f, 1.0f, -4.0f);
        bishop->draw();
    }
    glPopMatrix();

    //Black Queen
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-6.0f, 1.0f, -2.0f);
        queen->draw();
    }
    glPopMatrix();

    //Black Pawn 1
    for (size_t i = 0; i < originalBlackPawnPositions.size(); i++) {
        textureManager->useTexture("darkMarble");
        glPushMatrix(); {
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(currentBlackPawnPositions[i].x, currentBlackPawnPositions[i].y, currentBlackPawnPositions[i].z);
            pawn->draw();
        }
        glPopMatrix();
    }

    //Black Pawn 2
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-4.0f, 1.0f, 4.0f);
        pawn->draw();
    }
    glPopMatrix();

    //Black Pawn 3
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-4.0f, 1.0f, 2.0f);
        pawn->draw();
    }
    glPopMatrix();

    //Black Pawn 4
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-4.0f, 1.0f, 0.0f);
        pawn->draw();
    }
    glPopMatrix();

    //Black Pawn 5
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-4.0f, 1.0f, -2.0f);
        pawn->draw();
    }
    glPopMatrix();

    //Black Pawn 6
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-4.0f, 1.0f, -4.0f);
        pawn->draw();
    }
    glPopMatrix();

    //Black Pawn 7
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-4.0f, 1.0f, -6.0f);
        pawn->draw();
    }
    glPopMatrix();

    //Black Pawn 8
    textureManager->useTexture("darkMarble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-4.0f, 1.0f, -8.0f);
        pawn->draw();
    }
    glPopMatrix();

    //WHITE PIECES
    textureManager->useTexture("marble"); 
    for (size_t i = 0; i < originalWhiteRookOnePositions.size(); i++) {
        //White Rook 1
        glPushMatrix(); {
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(currentWhiteRookOnePositions[i].x, currentWhiteRookOnePositions[i].y, currentWhiteRookOnePositions[i].z);
            rook->draw();
        }
        glPopMatrix();
    }
    
    textureManager->useTexture("marble");
    for (size_t i = 0; i < originalWhiteRookTwoPositions.size(); i++) {
        //White Rook 2
        glPushMatrix(); {
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(currentWhiteRookTwoPositions[i].x, currentWhiteRookTwoPositions[i].y, currentWhiteRookTwoPositions[i].z);
            rook->draw();
        }
        glPopMatrix();
    }
    
    textureManager->useTexture("marble");
    for (size_t i = 0; i < originalWhiteKnightOnePositions.size(); i++) {
        //White Knight 1
        glPushMatrix(); {
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(currentWhiteKnightOnePositions[i].x, currentWhiteKnightOnePositions[i].y, currentWhiteKnightOnePositions[i].z);
            knight->draw();
        }
        glPopMatrix();
    }

    textureManager->useTexture("marble");
    for (size_t i = 0; i < originalWhiteKnightTwoPositions.size(); i++) {
        //White Knight 2
        glPushMatrix(); {
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(currentWhiteKnightTwoPositions[i].x, currentWhiteKnightTwoPositions[i].y, currentWhiteKnightTwoPositions[i].z);
            knight->draw();
        }
        glPopMatrix();
    }

    textureManager->useTexture("marble");
    for (size_t i = 0; i < originalWhitePawnPositions.size(); i++) {
        //White Pawn 1
        glPushMatrix(); {
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(currentWhitePawnPositions[i].x, currentWhitePawnPositions[i].y, currentWhitePawnPositions[i].z);
            pawn->draw();
        }
        glPopMatrix();
    }

    //White Pawn 2
    textureManager->useTexture("marble");
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(6.0f, 1.0f, 4.0f);
        pawn->draw();
    }
    glPopMatrix(); 

    //White Pawn 3
    textureManager->useTexture("marble");
    glPushMatrix(); { 
        glColor3f(1.0f, 1.0f, 1.0f); 
        glTranslatef(6.0f, 1.0f, 2.0f); 
        pawn->draw(); 
    }
    glPopMatrix(); 

    //White Pawn 4
    textureManager->useTexture("marble");
    glPushMatrix(); { 
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(6.0f, 1.0f, 0.0f);
        pawn->draw(); 
    }
    glPopMatrix(); 

    //White Pawn 5
    textureManager->useTexture("marble"); 
    glPushMatrix(); { 
        glColor3f(1.0f, 1.0f, 1.0f); 
        glTranslatef(6.0f, 1.0f, -2.0f); 
        pawn->draw(); 
    }
    glPopMatrix();   

    //White Pawn 6
    textureManager->useTexture("marble");
    glPushMatrix(); { 
        glColor3f(1.0f, 1.0f, 1.0f); 
        glTranslatef(6.0f, 1.0f, -4.0f);
        pawn->draw(); 
    }
    glPopMatrix();

    //White Pawn 7
    textureManager->useTexture("marble");
    glPushMatrix(); { 
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(6.0f, 1.0f, -6.0f);
        pawn->draw(); 
    }
    glPopMatrix();

    //White Pawn 8
    textureManager->useTexture("marble");
    glPushMatrix(); { 
        glColor3f(1.0f, 1.0f, 1.0f); 
        glTranslatef(6.0f, 1.0f, -8.0f);
        pawn->draw(); 
    }
    glPopMatrix(); 
     
    textureManager->useTexture("marble");
    //White King
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, -0.0f);
        king->draw();
    }
    glPopMatrix();

    textureManager->useTexture("marble");
    //White Bishop 1
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, 2.0f);
        bishop->draw();
    }
    glPopMatrix();

    textureManager->useTexture("marble");
    //White Bishop 2
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, -4.0f);
        bishop->draw();
    }
    glPopMatrix();

    textureManager->useTexture("marble");
    //White Queen
    glPushMatrix(); {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(8.0f, 1.0f, -2.0f);
        queen->draw();
    }
    glPopMatrix();



  //TERRAIN 
    textureManager->useTexture("grass");
    glPushMatrix(); {
        terrain->draw();
    }
    glPopMatrix();

    //ChessBoard 
    textureManager->useTexture("water");
    glPushMatrix(); {
        glRotatef(-90, 1, 0, 0);
        glScalef(2.0f, 2.0f, 1.0f);
        chessboard->draw();
    }
    glPopMatrix();

    //BORDER
    textureManager->useTexture("sand"); 
    glPushMatrix(); {
        glTranslatef(1.0f, 0.0f, -1.0f);
        //glRotatef(-90, 1, 0, 0); 
        //glScalef(2.0f, 2.0f, 2.0f);
        border->draw();  
    }
    glPopMatrix();

    Input::updateAfter();  
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
            originalBlackRookOnePositions.push_back(glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5));
            currentBlackRookOnePositions.push_back(originalBlackRookOnePositions.back());
            break;
        case 'k':
            // Add a new knight at a random position
            originalBlackKnightOnePositions.push_back(glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5));
            currentBlackKnightOnePositions.push_back(originalBlackKnightOnePositions.back());
            break;
        case ' ':
            if (!isAnimating) {
                // Start the animation
                targetBlackRookOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetBlackRookTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetBlackKnightOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5); 
                targetBlackKnightTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetBlackPawnPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetWhiteRookOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetWhiteRookTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetWhiteKnightOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetWhiteKnightTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
                targetWhitePawnPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
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
    // This function should update the targetRookPosition
    //  set the new target position.

    if (isAnimating) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - animationStartTime;

        if (elapsedTime >= animationDuration) {
            // Animation is complete, set a new target position.
            targetBlackRookOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetBlackRookTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetBlackKnightOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetBlackKnightTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetWhiteRookOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetWhiteRookTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetWhiteKnightOnePosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetWhiteKnightTwoPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetBlackPawnPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            targetWhitePawnPosition = glm::vec3(rand() % 10 - 5, 1.0f, rand() % 10 - 5);
            animationStartTime = currentTime; // Reset animation start time
        }
    }
}





