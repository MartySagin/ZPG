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
    for (auto& object : objects)
    {  
        object->Draw();  
    }
}


void Scene::AddObject(DrawableObject* object)
{
    objects.push_back(object);
}

Camera* Scene::GetCamera()
{
    return this->camera;
}

Light* Scene::GetLight()
{
	return this->light;
}

