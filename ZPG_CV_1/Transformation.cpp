#include "Transformation.h"

Transformation::Transformation()
{
}

void Transformation::AddComponent(TransformationComponent* component)
{
    this->components.push_back(component);
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

Transformation::~Transformation()
{
    for (auto component : this->components)
    {
        delete component;
    }
}
