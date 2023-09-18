#include "Terrain.h"
#include <iostream>
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


Terrain::Terrain(const char* heightmapPath) {
    // Initialize member variables and load heightmap
    width = 50; 
    height = 50;
    textureID = 0;
    loadHeightmap(heightmapPath);
    generateTerrain();
    setupMesh();
    loadTexture("../Textures/HeightMap3.png"); // Change to your texture path
}

Terrain::~Terrain() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
}

void Terrain::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    // Use appropriate shader program
    Shader shader("vertex_shader.glsl", "fragment_shader.glsl"); 
    shader.use(); 

    // Set shader uniforms for view and projection matrices
    shader.setMat4("view", viewMatrix); 
    shader.setMat4("projection", projectionMatrix); 


    // Bind the terrain texture
    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0 
    glBindTexture(GL_TEXTURE_2D, textureID);  
    shader.setInt("terrainTexture", 0); // Set the shader uniform for the texture 
     
    // Set shader uniforms for view and projection matrices

    // Bind VAO and draw
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Terrain::loadHeightmap(const char* heightmapPath) {
    // Load heightmap image using stb_image.h
     unsigned char* image = stbi_load("../Textures/HeightMap3.png", &width, &height, NULL, 1);

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
    float stepX = 1.0f; 
    float stepY = 1.0f; // Adjust as needed

    // Calculate the number of vertices in the x and y directions
    int numVerticesX = width; 
    int numVerticesY = height; // Assuming 1 vertex per pixel

    // Create vertices
    for (int y = 0; y < numVerticesY; ++y) {
        for (int x = 0; x < numVerticesX; ++x) {
            // Calculate the vertex position based on image dimensions and step size
            float posX = static_cast<float>(x) * stepX;
            float posY = static_cast<float>(y) * stepY;

            // Get the height value from the height data
            float heightValue = 5.0f; //vertices[y * numVerticesX + x]; // Adjust for your height data format

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
    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Specify vertex attributes (position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glBindVertexArray(0);
}

void Terrain::loadTexture(const char* texturePath) {
    // Use the same heightmap image as the texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters (e.g., filtering, wrapping)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Load the heightmap data as the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, &vertices[0]);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

