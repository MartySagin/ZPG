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

	
	glDepthFunc(GL_LEQUAL); 
	glDepthMask(GL_FALSE);  

	if (this->skybox) {
		this->skybox->GetShaderProgram()->UseProgram();

		this->skybox->GetShaderProgram()->SetIntUniform("followSkybox", this->followSkybox);

		this->skybox->Draw(); 
	}

	glDepthMask(GL_TRUE); 
	glDepthFunc(GL_LESS);
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

void Scene::SetSkybox(DrawableObject* skybox)
{
	this->skybox = skybox;
}

void Scene::SetFollowSkybox(bool followSkybox)
{
	this->followSkybox = followSkybox;
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

DrawableObject* Scene::GetSkybox()
{
	return this->skybox;
}

bool Scene::GetFollowSkybox()
{
	return this->followSkybox;
}
