#include "../include/Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::cout << "Shader: Reading vertex shader from " << vertexPath << std::endl;
    std::string vertexCode = readShader(vertexPath);

    std::cout << "Shader: Reading fragment shader from " << fragmentPath << std::endl;
    std::string fragmentCode = readShader(fragmentPath);

    std::cout << "Shader: Compiling vertex shader..." << std::endl;
    GLuint vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);

    std::cout << "Shader: Compiling fragment shader..." << std::endl;
    GLuint fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

    std::cout << "Shader: Linking shaders into a program..." << std::endl;
    programID = linkShaders(vertexShader, fragmentShader);

    // Clean up compiled shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    std::cout << "Shader: Deleting shader program with ID " << programID << std::endl;
    glDeleteProgram(programID);
}

void Shader::use() {
    glUseProgram(programID);
}

void Shader::setUniform(const std::string& name, float value) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << std::endl;
    } else {
        glUniform1f(location, value);
        
    }
}

void Shader::setUniform(const std::string& name, float x, float y, float z, float w) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << std::endl;
    } else {
        glUniform4f(location, x, y, z, w);
    }
}

void Shader::setUniform(const std::string& name, Mat4<float> &_mvp)
{
    float *mvparray = new float[16];

    mvparray[0]= _mvp.r1.x;
    mvparray[1]= _mvp.r2.x;
    mvparray[2]= _mvp.r3.x;
    mvparray[3]= _mvp.r4.x;

    mvparray[4]= _mvp.r1.y;
    mvparray[5]= _mvp.r2.y;
    mvparray[6]= _mvp.r3.y;
    mvparray[7]= _mvp.r4.y;

    mvparray[8]= _mvp.r1.z;
    mvparray[9]= _mvp.r2.z;
    mvparray[10]= _mvp.r3.z;
    mvparray[11]= _mvp.r4.z;

    mvparray[12]= _mvp.r1.w;
    mvparray[13]= _mvp.r2.w;
    mvparray[14]= _mvp.r3.w;
    mvparray[15]= _mvp.r4.w;

    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << std::endl;
    } else {
        glUniformMatrix4fv(location,1,GL_FALSE,mvparray);
    }

    delete mvparray;
}


std::string Shader::readShader(const char* filePath) {
    std::ifstream file(filePath, std::ios::in);
    std::ostringstream buffer;

    try {
        if (!file.is_open()) {
            throw std::ios_base::failure("Could not open file");
        }
        buffer << file.rdbuf();
        file.close();
        std::cout << "Shader: Successfully read file " << filePath << std::endl;
    } catch (const std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << filePath << "\n";
    }

    return buffer.str();
}

GLuint Shader::compileShader(const char* shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
    } else {
        std::cout << (shaderType == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader")
                  << " compiled successfully!" << std::endl;
    }

    return shader;
}

GLuint Shader::linkShaders(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << "\n";
    } else {
        std::cout << "Shader Program linked successfully!" << std::endl;
    }

    return program;
}
