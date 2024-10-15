
#pragma once
#include <glm/glm.hpp>

class Transformation
{
public:
    glm::mat4 transform;

    Transformation();

    virtual void SetPosition(glm::vec3 position);  
    virtual void SetRotation(glm::vec3 rotationDegrees);
    virtual void SetScale(glm::vec3 scale);

    virtual glm::mat4 GetMatrix() const;
    virtual ~Transformation() = default;  
};