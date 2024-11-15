#include "Translate.h"

Translate::Translate(glm::vec3 translation) : translation(translation)
{
}

glm::mat4 Translate::Apply(glm::mat4 model)
{ 
	return glm::translate(model, this->translation);
}
