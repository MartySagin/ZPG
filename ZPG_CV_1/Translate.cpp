#include "Translate.h"

Translate::Translate(float x, float y, float z) : translation(x, y, z)
{
}

glm::mat4 Translate::Apply(glm::mat4 model)
{ 
	return glm::translate(model, this->translation);
}
