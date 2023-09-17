#include "Terrain.h"
#include <iostream>
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <Shader.h>


Terrain::Terrain(const char* heightmapPath) {
    loadHeightmap(heightmapPath);
    generateTerrain();
    setupMesh();
    loadTexture("../Textures/HeightMap2.png"); // Change to your texture path
}

Terrain::~Terrain() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
}

void Terrain::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    // Use appropriate shader program

    // Bind the terrain texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set shader uniforms for view and projection matrices

    // Bind VAO and draw
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Terrain::loadHeightmap(const char* heightmapPath) {
    // Load heightmap image using stb_image.h
     unsigned char* image = stbi_load(heightmapPath, &width, &height, NULL, 1);

     if (!image) {
        std::cerr << "Failed to load heightmap image." << std::endl;
        return;
     }

     // Clear the current height data vector
     vertices.clear();

    // Store height data in a vector
     for (int y = 0; y < height; ++y) {
         for (int x = 0; x < width; ++x) {
             // Assuming each pixel represents the height (grayscale)
             float heightValue = static_cast<float>(image[y * width + x]) / 255.0f;
             vertices.push_back(heightValue); // Store the height value in the vector
         }
     }
     // Free the image data since we have stored it in vertices
     stbi_image_free(image);
}

void Terrain::generateTerrain() {
    // Clear existing vertices and indices
    vertices.clear();
    indices.clear();

    // Calculate the step size between terrain points
    float stepX = 1.0f; // Adjust as needed
    float stepY = 1.0f; // Adjust as needed

    // Calculate the number of vertices in the x and y directions
    int numVerticesX = width; // Assuming 1 vertex per pixel
    int numVerticesY = height; // Assuming 1 vertex per pixel

    // Create vertices
    for (int y = 0; y < numVerticesY; ++y) {
        for (int x = 0; x < numVerticesX; ++x) {
            // Calculate the vertex position based on image dimensions and step size
            float posX = static_cast<float>(x) * stepX;
            float posY = static_cast<float>(y) * stepY;

            // Get the height value from the height data
            float heightValue = vertices[y * numVerticesX + x]; // Adjust for your height data format

            // Create the vertex (assuming a simple flat terrain with no variation in the Z-axis)
            vertices.push_back(posX);
            vertices.push_back(posY);
            vertices.push_back(heightValue);

            // Texture coordinates (you can calculate these as needed)
            float texCoordX = static_cast<float>(x) / static_cast<float>(numVerticesX - 1);
            float texCoordY = static_cast<float>(y) / static_cast<float>(numVerticesY - 1);
            vertices.push_back(texCoordX);
            vertices.push_back(texCoordY);
        }
    }

    // Create indices for rendering as triangles
    for (int y = 0; y < numVerticesY - 1; ++y) {
        for (int x = 0; x < numVerticesX - 1; ++x) {
            // Calculate indices for the current quad
            int topLeft = y * numVerticesX + x;
            int topRight = topLeft + 1;
            int bottomLeft = (y + 1) * numVerticesX + x;
            int bottomRight = bottomLeft + 1;

            // Define two triangles for the quad
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}


void Terrain::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Specify vertex attributes (position, normals, texture coordinates)

    glBindVertexArray(0);
}

void Terrain::loadTexture(const char* texturePath) {
    // Load and generate the terrain texture
    // Set texture parameters (e.g., filtering, wrapping)
}
