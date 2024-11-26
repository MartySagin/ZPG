#pragma once

#include "Scale.h"

class DynamicScale : public Scale
{
    private:
	    glm::vec3 velocity;

        float deltaTime;

    public:
        DynamicScale(glm::vec3 scaling, glm::vec3 velocity, float deltaTime);

        void Update();

        glm::mat4 GetMatrix() override;
};
