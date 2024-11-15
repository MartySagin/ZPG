#pragma once

#include "Translate.h"

class DynamicTranslate : public Translate
{
private:
    glm::vec3 velocity;

	float deltaTime;

public:
    DynamicTranslate(glm::vec3 translation, glm::vec3 velocity, float deltaTime);

    void Update() override; 

    glm::mat4 Apply(glm::mat4 model) override;
};
