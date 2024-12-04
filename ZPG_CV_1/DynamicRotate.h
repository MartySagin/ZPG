#pragma once

#include "Rotate.h"

class DynamicRotate : public Rotate
{
    private:
        glm::vec3 velocity;

	    float deltaTime;

    public:
        DynamicRotate(glm::vec3 rotation, glm::vec3 velocity, float deltaTime);

		void SetVelocity(glm::vec3 velocity);

		void SetRotation(glm::vec3 rotation);

        void Update(); 

	    glm::mat4 GetMatrix() override;
};
