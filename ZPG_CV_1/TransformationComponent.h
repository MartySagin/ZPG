#pragma once
#include <glm/glm.hpp>

class TransformationComponent
{
public:
    virtual glm::mat4 Apply(const glm::mat4& model) const = 0; 

    virtual ~TransformationComponent() = default;
};