#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Rotate : public TransformationComponent
{
    protected:
        glm::vec3 rotation;

    public:
        Rotate(glm::vec3 rotation);

        void Update() override {};

        glm::mat4 Apply(glm::mat4 model) override;
};
