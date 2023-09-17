#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

class Terrain {
public:
    Terrain(const char* heightmapPath);
    ~Terrain();

    void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

private:
    GLuint VAO, VBO, EBO, textureID;
    int width, height;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Helper functions
    void loadHeightmap(const char* heightmapPath);
    void generateTerrain();
    void setupMesh();
    void loadTexture(const char* texturePath);
};

#endif


