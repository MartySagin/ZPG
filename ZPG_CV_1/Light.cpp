#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 objectColor, float intensity)
{
	this->position = position;

	this->color = color;

	this->objectColor = objectColor;

	this->intensity = intensity;
}

glm::vec3 Light::GetPosition() 
{
	return this->position;
}

glm::vec3 Light::GetColor() 
{
	return this->color;
}

glm::vec3 Light::GetObjectColor() 
{
	return this->objectColor;
}

float Light::GetIntensity() 
{
	return this->intensity;
}


void Light::SetPosition(glm::vec3 newPosition)
{
	this->position = newPosition;

	this->NotifyObservers();
}

void Light::SetColor(glm::vec3 newColor)
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
