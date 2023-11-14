#include "Light.h"
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

unsigned int Light::currentId = 0;

Light::Light() {
	id = currentId;
	currentId++;
}

void Light::init() {
	GLenum lightEnum = GL_LIGHT0 + id; 
	glEnable(lightEnum); 

    if (isDirectional) {
        // Directional light setup
        glm::vec4 directionPosition = glm::vec4(direction, 0.0f); // Directional light position is actually its direction
        glLightfv(lightEnum, GL_POSITION, glm::value_ptr(directionPosition));
    }
    else {
        // Other light types (point light, spotlight) setup
        glLightfv(lightEnum, GL_POSITION, glm::value_ptr(position));
    }

    glLightfv(lightEnum, GL_DIFFUSE, glm::value_ptr(diffuse));
    glLightfv(lightEnum, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(lightEnum, GL_SPECULAR, glm::value_ptr(specular));

    if (isSpotlight) {
        glLightf(lightEnum, GL_SPOT_CUTOFF, spotCutoff);
        glLightf(lightEnum, GL_SPOT_EXPONENT, spotExponent);
        glm::vec4 spotDir = glm::vec4(spotDirection, 0.0f); // Spotlights need a direction as well
        glLightfv(lightEnum, GL_SPOT_DIRECTION, glm::value_ptr(spotDir));
    }
}

void Light::setPosition(glm::vec4 value) {
	position = value;
	glLightfv(GL_LIGHT0 + id, GL_POSITION, glm::value_ptr(position));
}

void Light::setAmbient(glm::vec4 value) {
	ambient = value;
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, glm::value_ptr(ambient));
}

void Light::setDiffuse(glm::vec4 value) {
	diffuse = value;
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, glm::value_ptr(diffuse));
}

void Light::setSpecular(glm::vec4 value) {
	specular = value;
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, glm::value_ptr(specular));
}

void Light::enable() {
	glEnable(GL_LIGHT0 + id);
}

void Light::disable() {
	glDisable(GL_LIGHT0 + id);
}

void Light::setDirectional(bool directional) {
    isDirectional = directional;
}

void Light::setDirection(glm::vec3 direction) {
    this->direction = direction;
}

void Light::enableDirectionalLight() {
    isDirectional = true;
}

void Light::disableDirectionalLight() {
    isDirectional = false;
}

void Light::setSpotlight(bool spotlight) {
    isSpotlight = spotlight;
}

void Light::setSpotDirection(glm::vec3 direction) {
    spotDirection = direction;
}

void Light::setSpotCutoff(float cutoff) {
    spotCutoff = cutoff;
}

void Light::setSpotExponent(float exponent) {
    spotExponent = exponent;
}

void Light::enableSpotlight() {
    isSpotlight = true;
}

void Light::disableSpotlight() {
    isSpotlight = false;
} 