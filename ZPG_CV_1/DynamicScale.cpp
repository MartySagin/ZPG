#include "DynamicScale.h"

DynamicScale::DynamicScale(glm::vec3 scaling, glm::vec3 velocity, float deltaTime)
	: Scale(scaling), velocity(velocity), deltaTime(deltaTime)
{
}

void DynamicScale::Update()
{
	this->scaling.x += this->velocity.x * this->deltaTime;
	this->scaling.y += this->velocity.y * this->deltaTime;
	this->scaling.z += this->velocity.z * this->deltaTime;
}

glm::mat4 DynamicScale::Apply(glm::mat4 model)
{
    model = glm::scale(model, this->scaling);

    return model;
}
