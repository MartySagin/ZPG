#pragma once

#include "Translate.h"

class DynamicTranslate : public Translate
{
    private:
        glm::vec3 velocity;

	    float deltaTime;

    public:
        DynamicTranslate(glm::vec3 translation, glm::vec3 velocity, float deltaTime);

		void SetVelocity(glm::vec3 velocity);

        void Update(); 

        glm::mat4 GetMatrix() override;
};
