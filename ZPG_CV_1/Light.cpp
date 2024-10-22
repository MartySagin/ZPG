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

	this->NotifyObservers();
}

void Light::SetColor(const glm::vec3& newColor)
{
	this->color = newColor;

	this->NotifyObservers();
}

void Light::SetIntensity(float newIntensity)
{
	this->intensity = newIntensity;

	this->NotifyObservers();
}

void Light::NotifyObservers()
{
	for (auto observer : this->observers)
	{
		observer->UpdateFromSubject();
	}
}

void Light::AddObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Light::RemoveObserver(Observer* observer)
{
	this->observers.erase(remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
}
