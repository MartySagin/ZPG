#include "Scene.h"

void Scene::Init(const vector<DrawableObject*> drawableObjects, Camera* camera, Light* light)
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

Camera* Scene::GetCamera() const {
    return this->camera;
}

Light* Scene::GetLight() const {
	return this->light;
}

