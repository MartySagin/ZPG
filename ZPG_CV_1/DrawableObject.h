#pragma once

#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject
{
public:
    Model model;

    ShaderProgram shaderProgram;

    Transformation transform;

    bool hasNormal;

    DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, Camera* camera, Light* light, bool withNormal);

    void Draw();
};
