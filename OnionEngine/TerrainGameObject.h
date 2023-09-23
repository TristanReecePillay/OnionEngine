#pragma once
#include <string>
#include "GameObject.h"
#include "Texture.h"

using namespace std;

    class TerrainGameObject : public GameObject
    {
    public:
        TerrainGameObject(Texture* heightMapTexture, float size, float height);

    private:
        float size;
        float height;
        Texture* heightMap;
        void drawGeometry() override;
    };

