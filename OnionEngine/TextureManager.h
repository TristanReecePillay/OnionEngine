#pragma once
#include <map>
#include <string>
#include "Texture.h"

using namespace std;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	void useTexture(string textureName);
	Texture* getTexture(string textureName);

private:
	map<string, Texture*> textures;
};
