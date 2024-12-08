#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "TransformationComponent.h"
#include "DynamicRotate.h"
#include "DynamicTranslate.h"
#include "DynamicScale.h"

using namespace std;

class Transformation
{
    private:
        vector<TransformationComponent*> components;

    public:
        Transformation();

        void AddComponent(TransformationComponent* component, bool addToFront = false);
    
        glm::mat4 GetModelMatrix();

		void ClearComponents();
    
        ~Transformation();
    
};
