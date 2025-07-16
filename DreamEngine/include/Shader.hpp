#pragma once

#include <string>
#include <GL/glew.h> // Include GLEW for OpenGL types
#include "./Vec3.hpp"

class Shader {
public:
    GLuint programID;

    // Constructor: Takes file paths to vertex and fragment shaders
    Shader(const char* vertexPath, const char* fragmentPath);

    // Use this shader program
    void use();

    // Utility to set a uniform (example: float value)
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, float x, float y, float z, float w);
    void setUniform(const std::string& name, Mat4<float>& _mvp);

    // Destructor
    ~Shader();

private:
    // Read shader source code from file
    std::string readShader(const char* filePath);

    // Compile shader source
    GLuint compileShader(const char* shaderSource, GLenum shaderType);

    // Link vertex and fragment shaders into a program
    GLuint linkShaders(GLuint vertexShader, GLuint fragmentShader);
};
