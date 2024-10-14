#pragma once

#include "Model.h"
#include "Shader.h"
#include <glm/glm.hpp>

class DrawableObject
{
public:
    Model model;         
    Shader shader;       
    glm::mat4 transform; 
    bool hasNormal;

    DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormals);

    void SetPosition(glm::vec3 position);
    void SetRotation(glm::vec3 rotationDegrees);
    void SetScale(glm::vec3 scale);

    void Draw();
};
