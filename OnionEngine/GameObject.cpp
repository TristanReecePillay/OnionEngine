#include "GameObject.h"
#include "Settings.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>

void GameObject::generateDisplayList() { 
    displayListId = glGenLists(1); //number indicates number of display lists 
    glNewList(displayListId, GL_COMPILE); { 
        drawGeometry(); 
    }
    glEndList();
    displayListGenerated = true; 
}

void GameObject::setPosition(float x, float y, float z) { 
    position = vec3(x, y, z); 
}

void GameObject::draw() { 
    glPushMatrix(); { 
        glTranslatef(position.x, position.y, position.z); 
        if (displayListGenerated) { 
            glCallList(displayListId);
        }
        else {
            drawGeometry();
        }

        //if (Settings::debug)
        //drawOrigin();
    }
    glPopMatrix();
}

void GameObject::drawGeometry() {
    //glRotatef(45, 1, 1, 0); // to rotate the cube
    glColor3f(1, 0, 0);
    glutSolidCube(1.0);
}

void GameObject::drawOrigin() {
    glDisable(GL_DEPTH_TEST);

    glBegin(GL_LINES); {
        // X-Axis
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(originSize, 0, 0);

        // Y-Axis
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, originSize, 0);

        // Z-Axis
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, originSize);
    }
    glEnd();

    // X-Cone
    glPushMatrix(); {
        glColor3f(1, 0, 0);
        glTranslatef(originSize, 0, 0);
        glRotatef(90, 0, 1, 0); // Rotate the cone 90 degrees in the Y-axis.
        glutSolidCone(0.05, 0.2, 8, 1);
    }
    glPopMatrix();

    // Y-Cone
    glPushMatrix(); {
        glColor3f(0, 1, 0);
        glTranslatef(0, originSize, 0);
        glRotatef(-90, 1, 0, 0); // Rotate the cone -90 degrees in the X-axis.
        glutSolidCone(0.05, 0.2, 8, 1);
    }
    glPopMatrix();

    // Z-Cone
    glPushMatrix(); {
        glColor3f(0, 0, 1);
        glTranslatef(0, 0, originSize);
        //glRotatef(0, 1, 0, 0); // No need to rotate the cone as it already faces "Up" (?)
        glutSolidCone(0.05, 0.2, 8, 1);
    }
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}


