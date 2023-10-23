#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

using namespace std;

TextureManager::TextureManager() {
	textures.insert({ "darkMarble", new Texture("../Textures/dark_marble.jpg") });
	textures.insert({ "marble", new Texture("../Textures/WhiteMarble.jpg") });
	textures.insert({ "gold", new Texture("../Textures/gold_block.png") });
	textures.insert({ "pink", new Texture("../Textures/pink_block.png") });
	textures.insert({ "sand", new Texture("../Textures/Sand.jpg") });
	textures.insert({ "grass", new Texture("../Textures/seamless-grass-texture.jpg") });
	textures.insert({ "heightmap", new Texture("../Textures/HeightMap4.jpg", 0) });
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