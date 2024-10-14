#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation() : transform(glm::mat4(1.0f)) {}

void Transformation::SetPosition(glm::vec3 position)
{
    transform = glm::translate(transform, position);
}

void Transformation::SetRotation(glm::vec3 rotationDegrees)
{
    transform = glm::rotate(transform, glm::radians(rotationDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotationDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotationDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Transformation::SetScale(glm::vec3 scale)
{
    transform = glm::scale(transform, scale);
}

glm::mat4 Transformation::GetMatrix() const
{
    return transform;
}
