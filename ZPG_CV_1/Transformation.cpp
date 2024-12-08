#include "Transformation.h"

Transformation::Transformation()
{
}

void Transformation::AddComponent(TransformationComponent* component, bool addToFront) {
    
    if (addToFront) {
        this->components.insert(this->components.begin(), component);
    }
    else {
        this->components.push_back(component);
    }
}

glm::mat4 Transformation::GetModelMatrix()
{
	
	glm::mat4 modelMatrix = (1.0f);
    
    for (auto component : this->components)
	{
        modelMatrix *= component->GetMatrix();
	}

	return modelMatrix;
}

void Transformation::ClearComponents()
{
	for (auto component : this->components)
	{
		delete component;
	}

	this->components.clear();
}

Transformation::~Transformation()
{
    for (auto component : this->components)
    {
        delete component;
    }
}
