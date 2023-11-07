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
	glEnable(GL_LIGHT0 + id);

	glLightfv(GL_LIGHT0 + id, GL_POSITION, glm::value_ptr(position));
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, glm::value_ptr(specular));
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