#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Scale : public TransformationComponent
{
    glm::vec3 scaling;

    public:
        Scale(glm::vec3 scaling) : scaling(scaling) {}

        glm::mat4 Apply(glm::mat4 model) override;
};

