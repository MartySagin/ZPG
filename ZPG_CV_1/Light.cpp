#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, glm::vec3 direction, int type)
{
	this->position = position;

	this->color = color;

	this->intensity = intensity;

	this->ambientStrength = ambientStrength;

	this->direction = direction;

	this->type = type;
}

glm::vec3 Light::GetPosition()
{
	return this->position;
}

glm::vec3 Light::GetColor() 
{
	return this->color;
}

float Light::GetIntensity() 
{
	return this->intensity;
}

float Light::GetAmbientStrength()
{
	return this->ambientStrength;
}

glm::vec3 Light::GetDirection()
{
	return this->direction;
}

int Light::GetType()
{
	return this->type;
}

int Light::GetIndex()
{
	return this->index;
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

void Light::SetAmbientStrength(float newAmbientStrength)
{
	this->ambientStrength = newAmbientStrength;

	this->NotifyObservers();
}

void Light::SetIndex(int index)
{
	this->index = index;
}

void Light::NotifyObservers()
{
	for (auto observer : this->observers)
	{
		observer->UpdateFromSubject(this);
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
