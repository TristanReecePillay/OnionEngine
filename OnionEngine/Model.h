#pragma once
#include "GameObject.h"
#include "ModelPart.h"
#include "Texture.h"
#include <string>
#include <vector>
#include <GL/freeglut.h>


class Model : public GameObject
{
public:
	Model(std::string path, std::string name);
	~Model();

private:
	void loadModel(std::string path, std::string name);
	void drawGeometry();

	std::vector<ModelPart> parts;
	std::vector<Texture*> textures;

};

