#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Shader
{

public:
    // Constructor: takes paths to vertex and fragment shader source files
    Shader(const char* vertexPath, const char* fragmentPath) {
        // Load and compile shaders
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexPath);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentPath);

        // Create shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for shader program linking errors
        GLint linkStatus;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
        if (!linkStatus) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        }

        // Delete the shaders as they're linked into the program now and no longer needed
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // Use the shader program
    void use() const {
        glUseProgram(shaderProgram);
    }

    // Unuse the shader program
    void unuse() const {
        glUseProgram(0);
    }

    // Set a uniform value for a mat4 variable
    void setMat4(const std::string& name, const glm::mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    // Add more functions for setting other types of uniform variables as needed

private:
    GLuint shaderProgram;

    // Function to compile a shader
    GLuint compileShader(GLenum shaderType, const char* shaderPath) {
        GLuint shader = glCreateShader(shaderType);
        std::string shaderCode;
        std::ifstream shaderFile;

        // Ensure ifstream objects can throw exceptions
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            // Open the shader file
            shaderFile.open(shaderPath);

            std::stringstream shaderStream;

            // Read file's buffer contents into streams
            shaderStream << shaderFile.rdbuf();

            // Close the shader file
            shaderFile.close();

            // Convert stream into a string
            shaderCode = shaderStream.str();
        }
        catch (const std::ifstream::failure& e) {
            std::cerr << "Error: Failed to read shader file: " << shaderPath << std::endl;
            return 0;
        }

        const char* shaderCodeCStr = shaderCode.c_str();
        glShaderSource(shader, 1, &shaderCodeCStr, nullptr);
        glCompileShader(shader);

        // Check compilation status and handle errors
        GLint compileStatus;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
        if (!compileStatus) {
            char infoLog[512];
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Shader compilation failed for: " << shaderPath << "\n" << infoLog << std::endl;
            return 0;
        }

        return shader;
    }
};

