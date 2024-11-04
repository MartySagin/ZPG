#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Translate : public TransformationComponent
{
    private:
        glm::vec3 translation;

    public:
        Translate(float x, float y, float z);

        glm::mat4 Apply(glm::mat4 model) override;
    
};
