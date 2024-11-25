#include "Scale.h"

Scale::Scale(glm::vec3 scaling) : scaling(scaling.x, scaling.y, scaling.z)
{
}

glm::mat4 Scale::GetMatrix()
{
	glm::mat4 result(1.0f);
    
    return glm::scale(result, this->scaling);
}

