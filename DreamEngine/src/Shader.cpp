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

Shader* Shader::CreateFromSource(const char* vertexSource, const char* fragmentSource) {
    Log::LogMessage("CreateFromSource called", LogLevel::INFO_LEVEL)    ;
    
    Shader* shader = new Shader();  // Use private constructor
    
    std::cout << "Shader: Compiling vertex shader from source..." << std::endl;
    GLuint vertexShader = shader->compileShader(vertexSource, GL_VERTEX_SHADER);

    std::cout << "Shader: Compiling fragment shader from source..." << std::endl;
    GLuint fragmentShader = shader->compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    std::cout << "Shader: Linking shaders into a program..." << std::endl;
    shader->programID = shader->linkShaders(vertexShader, fragmentShader);


        // ADD THIS — validate the program
    glValidateProgram(shader->programID);
    GLint status;
    glGetProgramiv(shader->programID, GL_VALIDATE_STATUS, &status);
    char log[512];
    glGetProgramInfoLog(shader->programID, 512, nullptr, log);
    Log::LogMessage("Validate status: " + std::to_string(status) + " log: " + std::string(log), LogLevel::INFO_LEVEL);

    // Clean up compiled shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shader;
}

// Private default constructor for CreateFromSource
Shader::Shader() : programID(0) {}

Shader::~Shader() {
    Log::LogMessage("Shader: Deleting shader program with ID " + std::to_string(programID), LogLevel::INFO_LEVEL);
    // glDeleteProgram(programID);
}

void Shader::use() {
    glUseProgram(programID);
}


void Shader::setUniform(GLuint programID, const std::string& name, float value) {


        GLint currentProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        std::cout << "Currently bound program: " << currentProgram << " | This shader programID: " << programID << "\n";
        GLint location = glGetUniformLocation(programID, name.c_str());
        if (location == -1) {
            std::cout << "Warning: Uniform '" << name << "' not found in shader program. It might be optimized out if not used.\n";
        } else {
            glUseProgram(programID);
            glUniform1f(location, value);
            glUseProgram(currentProgram);
        }
    }


void Shader::setUniformCurrent(const std::string& name,float value) {
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    std::cout << "Currently bound program: " << currentProgram << " | Setting uniform '" << name << "' to float(" << value << ")\n";
    GLint location = glGetUniformLocation(currentProgram, name.c_str());
    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' not found in currently active shader program. It might be optimized out if not used.\n";
    } else {
        glUniform1f(location, value);
    }
}


void Shader::setUniform(GLuint programID, const std::string& name, float x, float y) {

        GLint currentProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        std::cout << "Currently bound program: " << currentProgram << " | This shader programID: " << programID << "\n";
        GLint location = glGetUniformLocation(programID, name.c_str());
        if (location == -1) {
            std::cout << "Warning: Uniform '" << name << "' not found in shader program. It might be optimized out if not used.\n";
        } else {
            glUseProgram(programID);
            glUniform2f(location, x, y);
            glUseProgram(currentProgram);
        }
    }

void Shader::setUniformCurrent(const std::string& name, float x, float y) {
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    std::cout << "Currently bound program: " << currentProgram << " | Setting uniform '" << name << "' to vec2(" << x << ", " << y << ")\n";
    GLint location = glGetUniformLocation(currentProgram, name.c_str());
    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' not found in currently active shader program. It might be optimized out if not used.\n";
    } else {
        glUniform2f(location, x, y);
    }
}




void Shader::setUniform(GLuint programID, const std::string& name, float x, float y, float z, float w) {


        GLint currentProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        std::cout << "Currently bound program: " << currentProgram << " | This shader programID: " << programID << "\n";
        GLint location = glGetUniformLocation(programID, name.c_str());
        if (location == -1) {
            std::cout << "Warning: Uniform '" << name << "' not found in shader program. It might be optimized out if not used.\n";
        } else {
            glUseProgram(programID);
            glUniform4f(location, x, y, z, w);
            glUseProgram(currentProgram);
        }
    }
void Shader::setUniformCurrent(const std::string& name, float x, float y, float z, float w) {
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    std::cout << "Currently bound program: " << currentProgram << " | Setting uniform '" << name << "' to vec4(" << x << ", " << y << ", " << z << ", " << w << ")\n";
    GLint location = glGetUniformLocation(currentProgram, name.c_str());
    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' not found in currently active shader program. It might be optimized out if not used.\n";
    } else {
        glUniform4f(location, x, y, z, w);
    }
}


void Shader::setUniform(GLuint programID, const std::string& name, int value) {


        GLint currentProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        std::cout << "Currently bound program: " << currentProgram << " | This shader programID: " << programID << "\n";
        GLint location = glGetUniformLocation(programID, name.c_str());
        if (location == -1) {
            std::cout << "Warning: Uniform '" << name << "' not found in shader program. It might be optimized out if not used.\n";
        } else {
            glUseProgram(programID);
            glUniform1i(location, value);
            glUseProgram(currentProgram);
        }
    }

void Shader::setUniformCurrent(const std::string& name, int value) {
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    std::cout << "Currently bound program: " << currentProgram << " | Setting uniform '" << name << "' to int(" << value << ")\n";
    GLint location = glGetUniformLocation(currentProgram, name.c_str());
    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' not found in currently active shader program. It might be optimized out if not used.\n";
    } else {
        glUniform1i(location, value);
    }
}


void Shader::setUniform(GLuint programID, const std::string&    name, Mat4<float> &_mvp)
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


            GLint currentProgram;
            glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
            std::cout << "Currently bound program: " << currentProgram << " | This shader programID: " << programID << "\n";
            GLint location = glGetUniformLocation(programID, name.c_str());
            if (location == -1) {
                std::cout << "Warning: Uniform '" << name << "' not found in shader program. It might be optimized out if not used.\n";
            } else {
                glUseProgram(programID);
                glUniformMatrix4fv(location,1,GL_FALSE,mvparray);
                glUseProgram(currentProgram);
            }

            delete mvparray;
}

void Shader::setUniformCurrent(const std::string& name, Mat4<float>& _mvp) {
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

            GLint currentProgram;
            glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
            std::cout << "Currently bound program inside setUniformCurrent: " << currentProgram << " | Setting uniform '" << name << "' to Mat4\n";
            GLint location = glGetUniformLocation(currentProgram, name.c_str());
            if (location == -1) {
                std::cout << "Warning: Uniform '" << name << "' not found in currently active shader program. It might be optimized out if not used.\n";
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
        Log::LogMessage("ERROR::SHADER::COMPILATION_FAILED\n" + std::string(infoLog), LogLevel::ERROR_LEVEL);
    } else {
        Log::LogMessage((shaderType == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") + std::string(" compiled successfully!"), LogLevel::INFO_LEVEL);
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
        Log::LogMessage("ERROR::SHADER::LINKING_FAILED\n" + std::string(infoLog), LogLevel::ERROR_LEVEL);
    } else {
        Log::LogMessage("Shader Program linked successfully!", LogLevel::INFO_LEVEL);
    }

    return program;
}

Shader* Shader::GetDefaultShader(){
	static const char* vertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
 gl_Position = projection_matrix*view_matrix*model_matrix*vec4(aPos,1.0);
}
	)";

	static const char* fragmentShaderSource = R"(
#version 330 core

out vec4 vColor;



void main()
{
	vColor = vec4(0,0,1,1);
}
	)";

	static Shader* shader = Shader::CreateFromSource(vertexShaderSource, fragmentShaderSource);
	if (shader == nullptr) {
		throw std::runtime_error("Failed to create default shader");
	}
	return shader;
}
