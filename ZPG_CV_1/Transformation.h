#pragma once
#include <vector>
#include "TransformationComponent.h"
#include <glm/glm.hpp>

using namespace std;

class Transformation
{
    private:
            vector<TransformationComponent*> components;

            glm::mat4 modelMatrix = (1.0f);

    public:
        Transformation();

        void AddComponent(TransformationComponent* component);
    
        glm::mat4 GetMatrix();
    
        ~Transformation();
    
};
