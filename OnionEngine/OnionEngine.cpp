// SquareAnim.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "SphereGameObject.h"
#include "TextureManager.h"
#include "TexturedCube.h"
#include <glm/glm.hpp>
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

TextureManager* textureManager;

GameObject* gameObject;
SphereGameObject* sphere;
TexturedCube* texturedCube; 

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    int windowX = (int)(glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2;
    int windowY = (int)(glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2;

    glutInitWindowPosition(windowX, windowY);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Textured Cube");

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    init();
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

    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

    initGameObjects();
}

void initGameObjects() {
    textureManager = new TextureManager();

    gameObject = new GameObject();
    gameObject->setPosition(1, 0, 0);

    sphere = new SphereGameObject();
    sphere->setPosition(-1, 0, 0);

    texturedCube = new TexturedCube();
    texturedCube->generateDisplayList();
}

void cleanUp() {
    delete textureManager;
    delete gameObject;
    delete sphere;
    delete texturedCube;
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    glRotatef(60, 1, 1, 0);
    textureManager->useTexture("ice");
    texturedCube->draw();

    glutSwapBuffers();
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}




