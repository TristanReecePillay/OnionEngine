#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

using namespace std;

TextureManager::TextureManager() {
	textures.insert({ "brick", new Texture("../GameObject/Textures/bricks.png") });
	textures.insert({ "dirt", new Texture("../GameObject/Textures/dirt.png") });
	textures.insert({ "gold", new Texture("../GameObject/Textures/gold_block.png") });
	textures.insert({ "heightmap", new Texture("../GameObject/Textures/HeightMap3.png", 1) });
}

TextureManager::~TextureManager() {
	map<string, Texture*>::iterator it;
	for (it = textures.begin(); it != textures.end(); it++) {
		delete it->second;
	}
}

void TextureManager::useTexture(string textureName) {
	if (!textures.count(textureName)) {
		cout << "Warning: Texture does not exist!" << endl;
		return;
	}
	Texture* tex = textures[textureName];
	tex->use();
}

Texture* TextureManager::getTexture(string textureName) {
	if (!textures.count(textureName)) {
		cout << "Warning: Texture does not exist!" << endl;
		return nullptr;
	}


	return textures[textureName];
}