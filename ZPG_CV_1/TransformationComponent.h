#pragma once
#include <glm/glm.hpp>

class TransformationComponent
{
public:
    virtual glm::mat4 Apply(glm::mat4 model) = 0; 

    virtual ~TransformationComponent() = default;
};