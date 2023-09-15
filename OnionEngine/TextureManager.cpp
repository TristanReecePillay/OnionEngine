#include "TextureManager.h"
#include <iostream>

using namespace std;


TextureManager::TextureManager() {
	textures.insert({ "brick", new Texture("../Textures/bricks.png") });
	textures.insert({ "dirt", new Texture("../Textures/dirt.png") });
	textures.insert({ "gold", new Texture("../Textures/gold_block.png") });
	textures.insert({ "roach", new Texture("../Textures/VID-20230909-WA0018.gif") });
	textures.insert({ "ice", new Texture("../Textures/frosted_ice.png") });
	textures.insert({ "China", new Texture("../Textures/00000-3111328019.png") });
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