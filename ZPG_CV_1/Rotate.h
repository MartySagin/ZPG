#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Rotate : public TransformationComponent
{
    glm::vec3 rotation;

public:
    Rotate(const glm::vec3& rotation) : rotation(rotation) {}

    glm::mat4 Apply(const glm::mat4& model) const override;
};
