#pragma once

#include "Rotate.h"

class DynamicRotate : public Rotate
{
private:
    glm::vec3 velocity;

	float deltaTime;

public:
    DynamicRotate(glm::vec3 rotation, glm::vec3 velocity, float deltaTime);

    void Update() override; 

	glm::mat4 Apply(glm::mat4 model) override;
};
