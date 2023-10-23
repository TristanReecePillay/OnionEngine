#pragma once
#include "Texture.h"
#include <string>
#include "GameObject.h"

using namespace std;

class Rook: public GameObject
{

  private:
	 void drawGeometry() override;
};

