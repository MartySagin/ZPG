#include "Translate.h"

glm::mat4 Translate::Apply(glm::mat4 model)
{ 
	return glm::translate(model, translation);
}
