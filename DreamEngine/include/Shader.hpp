#pragma once

#include <string>
#include <GL/glew.h> // Include GLEW for OpenGL types
#include "./Vec3.hpp"
#include "ECS_Core/Log.hpp"

class Shader {
public:
    GLuint programID;

    // Constructor: Takes file paths to vertex and fragment shaders
    Shader(const char* vertexPath, const char* fragmentPath);
    
    // Constructor: Takes shader source code strings directly
    static Shader* CreateFromSource(const char* vertexSource, const char* fragmentSource);

    static Shader* GetDefaultShader();

    // Use this shader program
    void use();

    // Utility to set a uniform (example: float value) static functions which takes in the program ID as parameter and set the uniform for that program ID. This way we don't have to create a shader object in Lua, we can simply call these static functions with the program ID of the shader we want to set the uniform for.
    static void setUniform(GLuint programID, const std::string& name, float value);
    static void setUniform(GLuint programID, const std::string& name, float x, float y);
    static void setUniform(GLuint programID, const std::string& name, float x, float y, float z, float w);
    static void setUniform(GLuint programID, const std::string& name, int value);
    static void setUniform(GLuint programID, const std::string& name, Mat4<float>& _mvp);

    static void setUniformCurrent(const std::string& name, float value);
    static void setUniformCurrent(const std::string& name, float x, float y);
    static void setUniformCurrent(const std::string& name, float x, float y, float z, float w);
    static void setUniformCurrent(const std::string& name, int value);
    static void setUniformCurrent(const std::string& name, Mat4<float>& _mvp);

    // Destructor
    ~Shader();

private:
    // Private default constructor for CreateFromSource
    Shader();
    // Read shader source code from file
    std::string readShader(const char* filePath);

    // Compile shader source
    GLuint compileShader(const char* shaderSource, GLenum shaderType);

    // Link vertex and fragment shaders into a program
    GLuint linkShaders(GLuint vertexShader, GLuint fragmentShader);
};
