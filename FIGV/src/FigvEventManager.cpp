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

#include "FigvEventManager.h"
#include "imgui.h"
#include "FigvScene.h"

FigvEventManager* FigvEventManager::instance = NULL;

FigvEventManager::FigvEventManager() = default;

FigvEventManager* FigvEventManager::getInstance() {

    if (!instance) { instance = new FigvEventManager(); }
    return instance;
}

int* FigvEventManager::getCameraMovementip() {
    return &cameraMovement;
}

void FigvEventManager::processMouseClics(GLFWwindow* window, int button, int action, int mods) {
    getInstance()->mouseClics(window, button, action, mods);
}

void FigvEventManager::mouseClics(GLFWwindow* window, int button, int action, int mods) {

    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action);

    if (!io.WantCaptureMouse) {
        if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_PRESS)) {
            glfwGetCursorPos(window, &lastX, &lastY);
            dragging = true;
        } else if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_RELEASE)) {
            dragging = false;
        }
    }
}

void FigvEventManager::processMouseScroll(double yDisplacement) {
    getInstance()->mouseScroll(yDisplacement);
}

void FigvEventManager::mouseScroll(double yDisplacement) {
    FigvScene::dollyCamera(float(yDisplacement));
}

void FigvEventManager::processCursorPosition(double xPos, double yPos) {
    getInstance()->cursorPosition(xPos, yPos);
}

void FigvEventManager::cursorPosition(double xPos, double yPos) {
    if (dragging) {
        double xOffset = lastX - xPos;
        double yOffset = lastY - yPos;

        lastX = xPos;
        lastY = yPos;

        if (cameraMovement == 0) {
            FigvScene::orbitCamera(float(-xOffset), float(-yOffset));
        } else {
            FigvScene::panCamera(float(xOffset), float(yOffset));
        }
    }
}

void FigvEventManager::processKeyClick(GLFWwindow* window, int key, int scancode, int action, int mods) {
    const float trackSpeed = 1.0f;
    const float zoomIntensity = 5.0f; 
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                FigvScene::trackCamera(-trackSpeed, 0.0f); // Mover hacia arriba
                break;
            case GLFW_KEY_DOWN:
                FigvScene::trackCamera(trackSpeed, 0.0f); // Mover hacia abajo
                break;
            case GLFW_KEY_LEFT:
                FigvScene::trackCamera(0.0f, trackSpeed); // Mover hacia la derecha
                break;
            case GLFW_KEY_RIGHT:
                FigvScene::trackCamera(0.0f, -trackSpeed); // Mover hacia la izquierda
                break;
            case GLFW_KEY_2: 
                FigvScene::zoomCamera(-zoomIntensity); // Reducir FOV para hacer zoom in
                break;
            case GLFW_KEY_1:
                FigvScene::zoomCamera(zoomIntensity); // Aumentar FOV para hacer zoom out
                break;
        }
    }
}

#include <stdio.h>
