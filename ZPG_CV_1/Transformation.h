#pragma once

#include <glm/glm.hpp>

class Transformation
{
public:
    glm::mat4 transform;

    Transformation();

    void SetPosition(glm::vec3 position);
    void SetRotation(glm::vec3 rotationDegrees);
    void SetScale(glm::vec3 scale);

    glm::mat4 GetMatrix() const;  
};