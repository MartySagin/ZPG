#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(glm::vec3 rotation, glm::vec3 velocity, float deltaTime)
	: Rotate(rotation), velocity(velocity), deltaTime(deltaTime)
{
}

void DynamicRotate::Update()
{

    this->rotation.x += this->velocity.x * this->deltaTime;
    this->rotation.y += this->velocity.y * this->deltaTime;
    this->rotation.z += this->velocity.z * this->deltaTime;

    if (this->rotation.x > 360.0f) this->rotation.x -= 360.0f;
    if (this->rotation.y > 360.0f) this->rotation.y -= 360.0f;
    if (this->rotation.z > 360.0f) this->rotation.z -= 360.0f;

}

glm::mat4 DynamicRotate::Apply(glm::mat4 model)
{
	model = glm::rotate(model, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return model;
}
