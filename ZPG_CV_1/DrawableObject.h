#pragma once

#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject
{
public:
    Model model;
    Transformation transformation;

    ShaderProgram shaderProgram;

    bool hasNormal;

    DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal);

    void SetPosition(glm::vec3 position);
    void SetRotation(glm::vec3 rotationDegrees);
    void SetScale(glm::vec3 scale);

    void Draw();
};
