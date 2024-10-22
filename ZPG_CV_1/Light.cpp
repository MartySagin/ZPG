#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color, float intensity)
{
	this->position = position;

	this->color = color;

	this->intensity = intensity;
}

glm::vec3 Light::GetPosition() const
{
	return this->position;
}

glm::vec3 Light::GetColor() const
{
	return this->color;
}

float Light::GetIntensity() const
{
	return this->intensity;
}

void Light::SetPosition(const glm::vec3& newPosition)
{
	this->position = newPosition;
}

void Light::SetColor(const glm::vec3& newColor)
{
	this->color = newColor;
}

void Light::SetIntensity(float newIntensity)
{
	this->intensity = newIntensity;
}
