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

	int objectID = 0;

	if (this->skybox)
	{
		this->skybox->SetObjectID(objectID++);
	}

	for (auto& object : this->objects) 
	{
		object->SetObjectID(objectID++);
	}

}

void Scene::Render()
{

	glEnable(GL_STENCIL_TEST);

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	if (this->skybox) {
		glStencilFunc(GL_ALWAYS, this->skybox->GetObjectID(), 0xFF);

		this->skybox->Draw();
	}
	
	for (auto& object : this->objects)
    {  
		glStencilFunc(GL_ALWAYS, object->GetObjectID(), 0xFF);
		
		object->Draw();
    }

	glDisable(GL_STENCIL_TEST);
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

void Scene::SetSelectedPosition(glm::vec3 position)
{
	this->selectedPosition = position;
}

void Scene::SelectObject(int objectID)
{
	if (this->skybox) {
		if (this->skybox->GetObjectID() == objectID)
		{
			this->selectedObject = this->skybox;

			return;
		}
	}
	
	for (auto& object : this->objects)
	{
		if (object->GetObjectID() == objectID)
		{
			this->selectedObject = object;

			break;
		}
	}
}

void Scene::RemoveSelectedObject()
{

	if (this->selectedObject != nullptr) {
		if (this->selectedObject == this->skybox)
		{
			this->skybox = nullptr;

			return;
		}
		
		this->objects.erase(remove(this->objects.begin(), this->objects.end(), this->selectedObject), this->objects.end());

		this->selectedObject = nullptr;
	}
}

void Scene::InsertObject(glm::vec3 position)
{
	ModelObject* loginModel = new ModelObject();
	loginModel->GenerateModelFromOBJ("objects/login.obj");

	ShaderProgram* loginShader = new ShaderProgram(GL_TRIANGLES, 0, loginModel->GetIndicesCount());
	loginShader->AddShadersFromFiles("VertexShader.glsl", "PhongShader.glsl");

	this->camera->AddObserver(loginShader);

	loginShader->SetNumberOfLights((int)lights.size());

	for (auto& light : this->lights)
	{
		light->AddObserver(loginShader);
	}

	Material* woodMaterial = new Material(0.6f, 0.8f, 0.2f);

	Texture* woodTexture = new Texture();
	woodTexture->Load2DTexture("textures/wooden_fence.png");

	DrawableObject* loginObject = new DrawableObject(loginShader, loginModel, woodMaterial, woodTexture);
	loginObject->GetTransformation()->AddComponent(new Translate(position));

	this->objects.push_back(loginObject);

	this->camera->NotifyObservers();

	for (auto& light : this->lights)
	{
		light->NotifyObservers();
	}
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

glm::vec3 Scene::GetSelectedPosition()
{
	return this->selectedPosition;
}
