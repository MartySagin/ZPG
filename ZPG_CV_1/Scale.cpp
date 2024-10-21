#include "Scale.h"

glm::mat4 Scale::Apply(const glm::mat4& model) const
{
    return glm::scale(model, scaling);
}
