#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() const;
    void unuse() const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setInt(const std::string& name, int value) const;

private:
    GLuint shaderProgram;

    GLuint compileShader(GLenum shaderType, const char* shaderPath);
};

