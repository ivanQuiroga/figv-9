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

#pragma once

#ifndef FigvShader_h
#define FigvShader_h

#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class FigvShader {
    
public:
    
    FigvShader(const char* vertexPath, const char* fragmentPath);

    void use() const;

    void setUniform(const std::string &name, bool value) const;
    void setUniform(const std::string &name, int value) const;
    void setUniform(const std::string &name, float value) const;
    void setUniform(const std::string &name, const glm::vec3 &value);
    void setUniform(const std::string &name, glm::mat4 &value) const;
    
private:
    
    unsigned int program;
    int linkSuccess;
    
    void compileShader(int type, const char *&shaderCode, unsigned int &handler);
    int locateUniform(const std::string &name) const;
};

#endif /* FigvShader_h */
