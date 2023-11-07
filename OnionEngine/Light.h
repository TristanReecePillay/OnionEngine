#pragma once

#include <glm/glm.hpp>

class Light
{
private:
	unsigned int id = 0;
	glm::vec4 position = { 0, 0, 0, 1 };
	glm::vec4 diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
	glm::vec4 ambient = glm::vec4(1.0, 1.0, 1.0, 1.0);
	glm::vec4 specular = glm::vec4(1.0, 1.0, 1.0, 1.0);

public:
	static unsigned int currentId;
	Light();
	void init();
	void setPosition(glm::vec4 value);
	void setDiffuse(glm::vec4 value);
	void setAmbient(glm::vec4 value);
	void setSpecular(glm::vec4 value);
	void enable();
	void disable();
};

