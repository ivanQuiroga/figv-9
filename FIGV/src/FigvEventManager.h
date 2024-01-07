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

#ifndef FigvEventManager_h
#define FigvEventManager_h

#include <GLFW/glfw3.h>

class FigvEventManager {
    
public:
    
    static FigvEventManager *getInstance();
    
    ~FigvEventManager();
    
    int* getCameraMovementip();
    
    static void processMouseClics(GLFWwindow* window, int button, int action, int mods);
    static void processMouseScroll(double yDisplacement);
    static void processCursorPosition(double xPos, double yPos);
    
private:
    
    FigvEventManager();
    
    void mouseClics(GLFWwindow* window, int button, int action, int mods);
    void mouseScroll(double yDisplacement);
    void cursorPosition(double xPos, double yPos);

    double lastX = 0.0;
    double lastY = 0.0;
    bool dragging = false;
    
    int cameraMovement = 0;

    static FigvEventManager *instance;
};

#endif /* FigvEventManager_h */
