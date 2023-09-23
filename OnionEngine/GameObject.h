#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace glm;

class GameObject
{
private:
    float originSize = 1.0f;
    vec3 position;
    bool displayListGenerated = false;
    virtual void drawGeometry();
    void drawOrigin();
    GLuint displayListId;
public:
    void setPosition(float x, float y, float z);
    void generateDisplayList();
    void draw();
};

