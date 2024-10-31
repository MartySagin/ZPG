#include "Scale.h"

Scale::Scale(glm::vec3 scaling) : scaling(scaling)
{
}

glm::mat4 Scale::Apply(glm::mat4 model)
{
    return glm::scale(model, this->scaling);
}
