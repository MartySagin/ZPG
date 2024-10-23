#include "Scale.h"

glm::mat4 Scale::Apply(glm::mat4 model)
{
    return glm::scale(model, scaling);
}
