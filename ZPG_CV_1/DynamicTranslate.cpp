#include "DynamicTranslate.h"

DynamicTranslate::DynamicTranslate(glm::vec3 translation, glm::vec3 velocity, float deltaTime)
	: Translate(translation), velocity(velocity), deltaTime(deltaTime)
{
}

void DynamicTranslate::SetVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

void DynamicTranslate::Update()
{
    this->translation.x += this->velocity.x * this->deltaTime;
    this->translation.y += this->velocity.y * this->deltaTime;
    this->translation.z += this->velocity.z * this->deltaTime;
}

glm::mat4 DynamicTranslate::GetMatrix()
{
    Update();

	glm::mat4 result(1.0f);
    
    return glm::translate(result, this->translation);
}
