#include "Scene.h"

void Scene::Init(vector<DrawableObject*> drawableObjects, Camera* camera, vector<Light*> lights)
{
	this->camera = camera;

	this->objects = drawableObjects;

	this->lights = lights;

	for (auto& light : this->lights)
	{
		light->NotifyObservers();
	}

	this->camera->NotifyObservers();
}

void Scene::Render()
{
    for (auto& object : this->objects)
    {  
        object->Draw();  
    }
}


void Scene::AddObject(DrawableObject* object)
{
	this->objects.push_back(object);
}

Camera* Scene::GetCamera()
{
    return this->camera;
}

vector<Light*> Scene::GetLights()
{
	return this->lights;
}

vector<DrawableObject*> Scene::GetObjects()
{
	return this->objects;
}

