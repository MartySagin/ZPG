#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Scale : public TransformationComponent
{
    private:
        glm::vec3 scaling;

    public:
        Scale(float scaleValue);

        glm::mat4 Apply(glm::mat4 model) override;
};

