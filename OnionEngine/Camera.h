#pragma once
#include <string>
#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Camera
{
private:
    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 upVector;

    glm::vec3 cameraPositions[3] = {
    glm::vec3(0.0f, 15.0f, -30.0f),  // Camera 1 position
    glm::vec3(20.0f, 20.0f, 0.0f),  // Camera 2 position
    glm::vec3(0.1f, 40.0f, 0.0f) // Camera 3 position
    };

    int currentCamera = 0;
    float yaw = 0.0f;
    float pitch = 0.0f;
    bool freeMovement;

public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 upVector)
        : cameraPosition(position), cameraTarget(target), upVector(upVector), freeMovement(false) {}

    void applyCameraView() const {
        gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
            cameraTarget.x, cameraTarget.y, cameraTarget.z,
            upVector.x, upVector.y, upVector.z);
    }

    void toggleFreeMovement() {
        freeMovement = !freeMovement;
    }

    void moveForward(float distance) {
        if (freeMovement) {
            glm::vec3 direction = glm::normalize(cameraTarget - cameraPosition);
            cameraPosition += direction * distance;
            cameraTarget += direction * distance;
        }
    }

    void moveBack(float distance) {
        if (freeMovement) {
            glm::vec3 direction = -glm::normalize(cameraTarget - cameraPosition);
            cameraPosition += direction * distance;
            cameraTarget += direction * distance;
        }
    }

    void moveRight(float distance) {
        if (freeMovement) {
            glm::vec3 rightVec = glm::normalize(glm::cross(cameraTarget - cameraPosition, upVector));
            cameraPosition += rightVec * distance;
            cameraTarget += rightVec * distance;
        }
    }

    void moveLeft(float distance) {
        if (freeMovement) {
            glm::vec3 rightVec = glm::normalize(glm::cross(cameraTarget - cameraPosition, upVector));
            cameraPosition -= rightVec * distance;
            cameraTarget -= rightVec * distance;
        }
    }

    void switchToNextCamera() {
        currentCamera = (currentCamera + 1) % 3;
        updateCameraPositions();
    }

    void switchToPreviousCamera() {
        currentCamera = (currentCamera + 2) % 3; // +2 to go back modulo 3
        updateCameraPositions();
    }

    void updateCameraPositions() {
        cameraPosition = cameraPositions[currentCamera];
        // Update cameraTarget and upVector based on the new position if needed
    }

    void rotateView(float deltaX, float deltaY) {
        const float sensitivity = 0.1f;

    // Update yaw and pitch angles based on mouse movement
    yaw += deltaX * sensitivity;
    pitch += deltaY * sensitivity;

    // Limit pitch to avoid flipping the view
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    // Calculate new direction
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 newTarget = cameraPosition + glm::normalize(front);

    // Update upVector if necessary (e.g., for a free-look camera)
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    // Update the view matrix by using glm::lookAt
    cameraTarget = newTarget;
    }
};

