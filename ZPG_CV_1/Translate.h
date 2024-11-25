#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformationComponent.h"

class Translate : public TransformationComponent
{
    protected:
        glm::vec3 translation;

    public:
        Translate(glm::vec3 translation);

        glm::mat4 GetMatrix() override;
    
};
