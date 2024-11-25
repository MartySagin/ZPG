#pragma once
#include <glm/glm.hpp>

class TransformationComponent
{
public:
    virtual glm::mat4 GetMatrix() = 0;

    virtual ~TransformationComponent() = default;
};