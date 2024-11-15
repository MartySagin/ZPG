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

        void Update() override {};

        glm::mat4 Apply(glm::mat4 model) override;
    
};
