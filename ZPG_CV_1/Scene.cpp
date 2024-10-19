#include "Scene.h"

void Scene::Init(const vector<DrawableObject*> drawableObjects, Camera* camera)
{
	this->camera = camera;
	this->objects = drawableObjects;
}

void Scene::Render()
{
    for (auto& object : objects)
    {
        object->Draw();  
    }
}

void Scene::Update()
{
	this->camera->NotifyObservers();
}

void Scene::AddObject(DrawableObject* object)
{
    objects.push_back(object);
}

Camera* Scene::GetCamera() const {
    return this->camera;
}

