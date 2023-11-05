#pragma once
#include <map>
#include <string>
static class Input
{
private:
	static int prevMouseX;
	static int prevMouseY;
	static int mouseX;
	static int mouseY;
	static int mouseXCached;
	static int mouseYCached;

	static std::map<unsigned char, int> keysDown; // key held down
	static std::map<unsigned char, int> keysPressed; // first time key is pressed
	static std::map<unsigned char, int> keysReleased; // the frame that they key is released

public:
	static void mousePositionUpdate(int x, int y);
	static void keyboardUpdate(unsigned char key, int mouseX, int mouseY);
	static void keyboardUpUpdate(unsigned char key, int mouseX, int mouseY);

	static void updateBefore();
	static void updateAfter();

	static int getMouseX();
	static int getMouseY();
	static int getMouseDeltaX(bool inverted = false);
	static int getMouseDeltaY(bool inverted = false);
	static bool getKeyDown(unsigned char key);
	static bool getKeyPressed(unsigned char key);
	static bool getKeyReleased(unsigned char key);
	static void outputKeysMap(std::map<unsigned char, int> keysMap, std::string info);

};

