#pragma once
#include "Pixel.h"

class Texture
{

public:
	Texture(const char* path, int desiredChannels = 4);
	~Texture();
	void use();
	Pixel getPixelAt(int x, int y);
	int getWidth();
	int getHeight();
private:
	unsigned char* image;
	int width;
	int height;
	int channels;
	int desiredChannels;
	bool loaded = false;
	void loadTexture(const char* path);
};

