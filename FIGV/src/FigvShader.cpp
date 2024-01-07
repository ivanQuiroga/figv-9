//
// FIGV (Fundamentos de Informática Gráfica y Visualización)
// Master en Desarrollo de Software, Universidad de Granada.
//
// Juan Carlos Torres Cantero
// ETSIIT, Depto. Lenguajes y Sistemas Informáticos, Universidad de Granada, jctorres@ugr.es
//
// Francisco de Asís Conde Rodríguez
// EPS, Depto. Informática, Universidad de Jaén, fconde@ujaen.es
//

#include <stdio.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "FigvShader.h"
#include "FigvAuxiliaryFunctions.h"

FigvShader::FigvShader(const char* vertexPath, const char* fragmentPath) {
    
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        FigvLog("FigvShader", __LINE__, "Error: Shader file not succesfully read");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;

    compileShader(GL_VERTEX_SHADER, vShaderCode, vertex);
    compileShader(GL_FRAGMENT_SHADER, fShaderCode, fragment);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
    if(!linkSuccess)
    {
        GLint logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> infoLog(logLength);
        glGetProgramInfoLog(program, logLength, NULL, &infoLog[0]);
        FigvLog( "FigvShader", __LINE__, "Error: Shader linking failed" );
        FigvLog( "FigvShader", __LINE__, std::string(infoLog.begin(), infoLog.end()) );
        glDeleteProgram(program);
        exit(2);
    }

    glDetachShader(program, vertex);
    glDeleteShader(vertex);
    glDetachShader(program, fragment);
    glDeleteShader(fragment);
}

void FigvShader::compileShader(int type, const char *&shaderCode, unsigned int &shaderObject) {
    
    GLint compileSuccess;

    shaderObject = glCreateShader(type);
    glShaderSource(shaderObject, 1, &shaderCode, NULL);
    glCompileShader(shaderObject);
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compileSuccess);
    if(!compileSuccess)
    {
        GLint logLength = 0;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> infoLog(logLength);
        glGetShaderInfoLog(shaderObject, logLength, NULL, &infoLog[0]);
        FigvLog("FigvShader", __LINE__, "Error: Shader compilation failed");
        FigvLog("FigvShader", __LINE__,  std::string(infoLog.begin(), infoLog.end()) );
        glDeleteShader(shaderObject);
        exit(1);
    };
}

void FigvShader::use() const {
    
    if (linkSuccess) {
        glUseProgram(program);
    } else {
        FigvLog("FigvShader", __LINE__, "Error: Attempt to use an invalid shader");
    }
}

int FigvShader::locateUniform(const std::string &name) const {
    
    GLint location;
    location = glGetUniformLocation(program, name.c_str());
    if (location < 0) {
        FigvLog("FigvShader", __LINE__, "Cannot find location for uniform: " + name);
    }
    return location;
}

void FigvShader::setUniform(const std::string &name, bool value) const {
    
    GLint uniformLocation = locateUniform(name);
    if (uniformLocation >= 0) {
        glUniform1i(uniformLocation, (int)value);
    }
}

void FigvShader::setUniform(const std::string &name, int value) const {
    
    GLint uniformLocation = locateUniform(name);
    if (uniformLocation >= 0) {
        glUniform1i(uniformLocation, (int)value);
    }
}

void FigvShader::setUniform(const std::string &name, float value) const {
    
    GLint uniformLocation = locateUniform(name);
    if (uniformLocation >= 0) {
        glUniform1f(uniformLocation, (float)value);
    }
}

void FigvShader::setUniform(const std::string &name, const glm::vec3 &value) {
    
    GLint uniformLocation = locateUniform(name);
    if (uniformLocation >= 0) {
        glUniform3f(uniformLocation, value.x, value.y, value.z);
    }
}

void FigvShader::setUniform(const std::string &name, glm::mat4 &value) const {
    
    GLint uniformLocation = locateUniform(name);
    if (uniformLocation >= 0) {
        glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(value));
    }
}
