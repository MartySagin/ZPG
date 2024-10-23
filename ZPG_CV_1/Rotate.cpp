#include "Rotate.h"


glm::mat4 Rotate::Apply(glm::mat4 model)
{
    glm::mat4 result = model;

    result = glm::rotate(result, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    result = glm::rotate(result, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    result = glm::rotate(result, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    return result;
}
