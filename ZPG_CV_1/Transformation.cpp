#include "Transformation.h"

Transformation::Transformation()
{
}

void Transformation::AddComponent(TransformationComponent* component)
{
    components.push_back(component);
}

glm::mat4 Transformation::GetMatrix() const
{
    glm::mat4 matrix = glm::mat4(1.0f);

    for (const auto& component : components)
    {
        matrix = component->Apply(matrix);
    }

    return matrix;
}

Transformation::~Transformation()
{
    for (auto component : components)
    {
        delete component;
    }
}
