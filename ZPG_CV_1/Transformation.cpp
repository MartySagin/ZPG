#include "Transformation.h"

Transformation::Transformation()
{
}

void Transformation::AddComponent(TransformationComponent* component)
{
    components.push_back(component);

	this->modelMatrix = component->Apply(this->modelMatrix);
}

glm::mat4 Transformation::GetMatrix()
{
    return modelMatrix;
}

Transformation::~Transformation()
{
    for (auto component : components)
    {
        delete component;
    }
}
