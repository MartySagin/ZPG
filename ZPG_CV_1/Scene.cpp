#include "Scene.h"

void Scene::Init(vector<DrawableObject*> drawableObjects, Camera* camera, Light* light)
{
	this->camera = camera;

	this->objects = drawableObjects;

	this->light = light;

	this->light->NotifyObservers();

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

Light* Scene::GetLight()
{
	return this->light;
}

vector<DrawableObject*> Scene::GetObjects()
{
	return this->objects;
}

