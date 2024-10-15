#pragma once

#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject : public Transformation
{
public:
    Model model;

    ShaderProgram shaderProgram;

    bool hasNormal;

    DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, Camera* camera, bool withNormal);

    void SetPosition(glm::vec3 position) override; 
    void SetRotation(glm::vec3 rotationDegrees) override;
    void SetScale(glm::vec3 scale) override;

    void Draw();
};
