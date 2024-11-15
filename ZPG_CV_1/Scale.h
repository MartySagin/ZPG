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

        void Update() override {};

        glm::mat4 Apply(glm::mat4 model) override;
};

