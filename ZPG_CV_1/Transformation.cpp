#include "Transformation.h"

Transformation::Transformation()
{
}

void Transformation::AddComponent(TransformationComponent* component)
{
    this->components.push_back(component);

	this->modelMatrix = component->Apply(this->modelMatrix);
}

glm::mat4 Transformation::GetModelMatrix()
{
    return this->modelMatrix;
}

Transformation::~Transformation()
{
    for (auto component : this->components)
    {
        delete component;
    }
}
