#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, glm::vec3 direction, float cutOff, float outerCutOff, int type)
{
	this->position = position;

	this->color = color;

	this->intensity = intensity;

	this->ambientStrength = ambientStrength;

	this->direction = direction;

	this->cutOff = cutOff;

	this->outerCutOff = outerCutOff;

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

float Light::GetCutOff()
{
	return this->cutOff;
}

int Light::GetIndex()
{
	return this->index;
}

float Light::GetOuterCutOff()
{
	return this->outerCutOff;
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

void Light::SetDirection(glm::vec3 newDirection)
{
	this->direction = newDirection;

	this->NotifyObservers();
}

void Light::SetCutOff(float newCutOff)
{
	this->cutOff = newCutOff;

	this->NotifyObservers();
}

void Light::SetOuterCutOff(float newOuterCutOff)
{
	this->outerCutOff = newOuterCutOff;

	this->NotifyObservers();
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

	this->NotifyObservers();
}

void Light::RemoveObserver(Observer* observer)
{
	this->observers.erase(remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());

	this->NotifyObservers();
}


void Light::UpdateFromSubject(Subject* subject)
{
	
	Camera* camera = (Camera*)subject;

	this->SetPosition(camera->GetPosition());

	this->SetDirection(camera->GetTarget());
	
}


