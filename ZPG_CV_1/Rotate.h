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

        glm::mat4 GetMatrix() override;
};
