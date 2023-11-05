#include "Input.h"
#include <sstream>
#include <iostream>

using namespace std;

int Input::prevMouseX;
int Input::prevMouseY;
int Input::mouseX;
int Input::mouseY;
int Input::mouseXCached;
int Input::mouseYCached;

map<unsigned char, int> Input::keysDown;
map<unsigned char, int> Input::keysPressed;
map<unsigned char, int> Input::keysReleased;


void Input::mousePositionUpdate(int x, int y) {
	cout << x << ", " << y << endl;
	mouseXCached = x;
	mouseYCached = y;
}

void Input::keyboardUpdate(unsigned char key, int mouseX, int mouseY) {
	//callback function telling us that a key is being held down
	//cout << "Key down: " << key << endl;

	//key is not in the keysDown map, then add it to the keysDown map
	if (keysDown.find(key) == keysDown.end()) {
		keysDown[key] = 0;
	}

	if (keysDown[key] == 0) {
		keysDown[key] = 1;
		keysPressed[key] = 1;
	}
	else if (keysDown[key] > 0) {
		keysDown[key]++;
	}
}

void Input::keyboardUpUpdate(unsigned char key, int mouseX, int mouseY) {
	// cout << "Key released: " << key << endl;

	keysReleased[key] = 1;
	keysDown[key] = 0;
}

void Input::updateBefore() {
	map<unsigned char, int>::iterator it;

	prevMouseX = mouseX;
	prevMouseY = mouseY;
	mouseX = mouseXCached;
	mouseY = mouseYCached;

	for (it = keysPressed.begin(); it != keysPressed.end(); ++it) {
		if (it->second == 0) {
			continue;
		}
		keysPressed[it->first]++;
	}

	for (it = keysReleased.begin(); it != keysReleased.end(); ++it) {
		if (it->second == 0) {
			continue;
		}
		keysReleased[it->first]++;
	}
}

void Input::updateAfter() {
	outputKeysMap(keysPressed, "pressed keys: ");
	outputKeysMap(keysDown, "down keys: ");
	outputKeysMap(keysReleased, "released keys: ");

	map<unsigned char, int>::iterator it;

	for (it = keysReleased.begin(); it != keysReleased.end(); ++it) {
		if (it->second > 1) {
			keysReleased[it->first] = 0;
		}
	}

	for (it = keysPressed.begin(); it != keysPressed.end(); ++it) {
		if (it->second > 1) {
			keysPressed[it->first] = 0;
		}
	}
}

void Input::outputKeysMap(map<unsigned char, int> keysMap, string info) {
	map<unsigned char, int>::iterator it;

	stringstream stream;
	string output;

	for (it = keysMap.begin(); it != keysMap.end(); ++it) {
		if (it->second > 0) {
			stream << it->first;
		}
	}
	stream >> output;
	if (!output.empty()) {
		cout << info << output << endl;
	}
}

int Input::getMouseX() {
	return mouseX;
}

int Input::getMouseY() {
	return mouseY;
}

int Input::getMouseDeltaX(bool inverted) {
	if (inverted) {
		return prevMouseX - mouseX;
	}
	return mouseX - prevMouseX;
}

int Input::getMouseDeltaY(bool inverted) {
	if (inverted) {
		return mouseY - prevMouseY;
	}
	return prevMouseY - mouseY;
}

bool Input::getKeyDown(unsigned char key) {
	return keysDown[key] > 0;
}

bool Input::getKeyPressed(unsigned char key) {
	return keysPressed[key] > 0;
}

bool Input::getKeyReleased(unsigned char key) {
	return keysReleased[key] > 0;
}
