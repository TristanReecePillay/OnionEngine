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

	bool isDirectional = false;
	glm::vec3 direction = glm::vec3(0.0, -1.0, 0.0); // Default downward direction for a directional light

	bool isSpotlight = false;
	glm::vec3 spotDirection = glm::vec3(0.0, -1.0, 0.0); // Default downward direction for a spotlight
	float spotCutoff = 45.0f; // Spotlight cutoff angle (default 45 degrees)
	float spotExponent = 1.0f; // Spotlight exponent (default 1.0)

public:
	static unsigned int currentId;
	Light();

	// Setters for general light properties
	void init();
	void setPosition(glm::vec4 value);
	void setDiffuse(glm::vec4 value);
	void setAmbient(glm::vec4 value);
	void setSpecular(glm::vec4 value);
	void enable();
	void disable();

	// Methods specific to directional lights
	void setDirectional(bool directional);
	void setDirection(glm::vec3 direction);
	void enableDirectionalLight();
	void disableDirectionalLight();

	// Methods specific to spotlight
	void setSpotlight(bool spotlight);
	void setSpotDirection(glm::vec3 direction);
	void setSpotCutoff(float cutoff);
	void setSpotExponent(float exponent);
	void enableSpotlight();
	void disableSpotlight();
};

