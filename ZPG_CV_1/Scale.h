#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Scale : public TransformationComponent
{
    glm::vec3 scaling;

    public:
        Scale(const glm::vec3& scaling) : scaling(scaling) {}

        glm::mat4 Apply(const glm::mat4& model) const override;
};

