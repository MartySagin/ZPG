#include "Scale.h"

Scale::Scale(float scaleValue) : scaling(scaleValue)
{
}

glm::mat4 Scale::Apply(glm::mat4 model)
{
    return glm::scale(model, this->scaling);
}
