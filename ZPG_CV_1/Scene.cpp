#include "Scene.h"

void Scene::Init(Camera* camera, vector<Light*> lights)
{
	this->camera = camera;

	this->lights = lights;

	for (auto& light : this->lights)
	{
		light->NotifyObservers();
	}
	
	this->camera->NotifyObservers();
}

void Scene::Render()
{
	
	if (this->skybox) {
		this->skybox->Draw();
	}
	
	for (auto& object : this->objects)
    {  
		object->Draw();  
    }

}

void Scene::Update(float deltaTime)
{
	this->animation.Update(deltaTime);
}

void Scene::AddObject(DrawableObject* object)
{
	this->objects.push_back(object);
}

void Scene::AddAnimation(function<void(float)> animation)
{
	this->animation.AddAnimation(animation);
}

void Scene::SetSkybox(Skybox* skybox)
{
	this->skybox = skybox;
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

Skybox* Scene::GetSkybox()
{
	return this->skybox;
}
