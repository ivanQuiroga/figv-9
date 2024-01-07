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

#ifndef FigvTexture_h
#define FigvTexture_h

#include <string>
#include "FigvShader.h"

struct FigvTexture {
    
public:
    FigvTexture(std::string path);
    
    void applyToShader(FigvShader shader);

private:
    // 1
    unsigned int textureID;
};

#endif /* FigvTexture_h */
