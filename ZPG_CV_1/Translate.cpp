#include "Translate.h"

Translate::Translate(glm::vec3 translation) : translation(translation)
{
}

glm::mat4 Translate::GetMatrix()
{ 
	glm::mat4 result(1.0f);
	
	return glm::translate(result, this->translation);
}
