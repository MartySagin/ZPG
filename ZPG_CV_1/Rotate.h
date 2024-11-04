#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Rotate : public TransformationComponent
{
    private:
        glm::vec3 rotation;

    public:
        Rotate(float angleX, float angleY, float angleZ);

        glm::mat4 Apply(glm::mat4 model) override;
};
