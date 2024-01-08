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
#include <glm/gtc/type_ptr.hpp>
#include "FigvScene.h"
#include "FigvAuxiliaryFunctions.h"

FigvScene* FigvScene::instance = nullptr;

FigvScene::FigvScene() {
    
    FigvLog("FigvScene", __LINE__, "Initializing the scene");
    
    camera = new FigvCamera();
    models = std::vector<Figv3DModel>();
    
    glm::mat4 R;
    // FIGV 15   
    R = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    FigvScene::importModel("./resources/models/spot/spot_trg.obj",
                                 new FigvMaterial(64.0, glm::vec3(1.0, 0.75, 0.75), glm::vec3(1.0)),
                                 "./resources/models/spot/spot_texture.png",
                                 R);
    R = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
    FigvScene::importModel("./resources/models/bob/bob_trg.obj",
                                 new FigvMaterial(),
                                 "./resources/models/bob/bob_teaser.png",
                                 R);
    FigvScene::importModel("./resources/models/blub/blub_trg.obj",
                                 new FigvMaterial(256.0, glm::vec3(0.4, 0.6, 1.0), glm::vec3(1.0)),
                                 "./resources/models/blub/blub_texture.png",
                                 glm::mat4(1.0));
    R = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    FigvScene::importModel("./resources/models/spot/spot_trg_2.obj",
                                 new FigvMaterial(64.0, glm::vec3(1.0, 0.75, 0.75), glm::vec3(1.0)),
                                 "./resources/models/spot/spot_texture.png",
                                 R);
    FigvScene::importModel("./resources/models/blub/blub_trg_2.obj",
                                 new FigvMaterial(256.0, glm::vec3(0.4, 0.6, 1.0), glm::vec3(1.0)),
                                 "./resources/models/blub/blub_texture.png",
                                 glm::mat4(1.0));

    lightSource = new FigvLightSource();
}

FigvScene::~FigvScene() = default;

FigvScene* FigvScene::getInstance() {
    
    if (!instance) { instance = new FigvScene(); }
    return instance;
}

void FigvScene::orbitCamera(float movementX, float movementY) {
    
    getInstance()->camera->orbit(movementX, movementY);
}

void FigvScene::panCamera(float movementX, float movementY) {
    
    getInstance()->camera->pan(movementX, movementY);
}

void FigvScene::dollyCamera(float distance) {
    
    getInstance()->camera->dolly(distance);
}

void FigvScene::trackCamera(float rightOffset, float upOffset) {

    FigvScene::getInstance()->camera->track(rightOffset, upOffset);
}

void FigvScene::zoomCamera(float deltaFovX) {
    FigvScene::getInstance()->camera->zoom(deltaFovX);
}

void FigvScene::importModel(const std::string& modelPath, FigvMaterial* material, const std::string texturePath, 
                         glm::mat4 transform) {
    models.push_back(Figv3DModel(modelPath, material, texturePath, transform));
}

void FigvScene::importDefaultModel(const std::string& modelPath, const std::string& texturePath) {
    FigvScene::importModel(modelPath, 
                            new FigvMaterial(32.0,           
                                                glm::vec3(1.0),   
                                                glm::vec3(1.0)    
                                            ),
                                            texturePath,
                                            glm::mat4(1.0));
}

void FigvScene::applyCameraPosition(FigvShader shader) {
    
    shader.setUniform("cameraPosition", getInstance()->camera->getPosition());
}

void FigvScene::drawScene(FigvShader shader) {
    
    glm::mat4 viewProj = getInstance()->camera->getViewProjectionMatrix();
    shader.setUniform("mViewProjection", viewProj);
    
    getInstance()->models[FigvScene::getInstance()->modelSelected].draw(shader);
}

void FigvScene::setFrameSize(int width, int height) {
    
    getInstance()->camera->setAspect(width, height);
}

float* FigvScene::getIa3fp() {
    
    return glm::value_ptr(Ia);
}

FigvLightSource* FigvScene::getLightSource() {
    
    return lightSource;
}

int* FigvScene::getUseModelingLightip() {
    
    return (int*)&useModelingLight;
}

void FigvScene::applyLightSources(FigvShader shader) {
    
    shader.setUniform("Ia", getInstance()->Ia);
    
    getInstance()->lightSource->applyIntensityToShader(shader);
    if (getInstance()->useModelingLight) {
        shader.setUniform("lightPosition", getInstance()->camera->getPosition());
    } else {
        getInstance()->lightSource->applyPositionToShader(shader);
    }
}

int* FigvScene::getModelSelectedip() {
    
    return &modelSelected;
}
