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

#ifndef FigvRenderer_h
#define FigvRenderer_h

#include <vector>
#include <glm/vec4.hpp>
#include "FigvShader.h"

class FigvRenderer {
    
public:
    
    ~FigvRenderer();
    
    static FigvRenderer *getInstance();
    
    static void renderScene();
    
    float* getBackgroundColor3fp();
    int* getRenderingModeip();
    float* getPointSizefp();
    
    int* getShaderActiveip();
    
    bool* getScaledNormalbp();
    
    bool* getCartoonSolidColorbp();
    int* getCartoonLevelsip();
    float* getCartoonMultiplierfp();
    float* getCartoonThresholdfp();
    
    // FIGV 17
    bool* getUseTexturebp();

    glm::vec3* getSkyColor3fv();
    glm::vec3* getGroundColor3fv();
    glm::vec3* getLightDirection3fv();
    
private:
    
    FigvRenderer();
    void render();
    
    static FigvRenderer *instance;
    
    glm::vec4 background;
    int renderingMode;
    float pointSize;
    
    int shaderActive;
    std::vector<FigvShader *> shaders;
    
    bool scaledNormal;
    
    bool cartoonSolidColor = false;
    int cartoonLevels = 4;
    float cartoonMultiplier = 7.0;
    float cartoonThreshold = 0.4;
    
    // FIGV 16
    bool useTexture;
    
    glm::vec3 skyColor{0.2f, 0.3f, 0.5f}; 
    glm::vec3 groundColor{0.1f, 0.1f, 0.1f}; 
    glm::vec3 lightDirection{0.0f, 1.0f, 0.0f}; 
    
};

#endif /* FigvRenderer_h */
