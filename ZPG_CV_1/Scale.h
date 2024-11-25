#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Scale : public TransformationComponent
{
    protected:
        glm::vec3 scaling;

    public:
        Scale(glm::vec3 scaling);

        glm::mat4 GetMatrix() override;
};

