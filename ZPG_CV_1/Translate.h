#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Translate : public TransformationComponent
{
    glm::vec3 translation;

public:
    Translate(const glm::vec3& translation) : translation(translation) {}

    glm::mat4 Apply(const glm::mat4& model) const override
    {
        return glm::translate(model, translation);
    }
};
