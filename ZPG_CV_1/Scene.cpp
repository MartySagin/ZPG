#include "Scene.h"

void Scene::Init(Camera* camera, vector<Light*> lights)
{
	
	this->camera = camera;

	this->lights = lights;

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

void Scene::AddObject(DrawableObject* object)
{
	this->objects.push_back(object);
}

void Scene::AddBezeirControlPoint(glm::vec3 controlPoint)
{
	if (this->selectedObject == nullptr)
	{
		return;
	}
	
	if (this->bezierControlPoints.size() == 4)
	{
		this->bezierControlPoints.clear();
	}
	
	this->bezierControlPoints.push_back(controlPoint);

	if (this->bezierControlPoints.size() == 4)
	{
		this->StartBezeirCurve();
	}
}

void Scene::StartBezeirCurve() {
	
	if (this->bezierControlPoints.size() != 4)
	{
		return;
	}

	if (this->selectedObject == nullptr)
	{
		return;
	}

	if (this->selectedObject == this->skybox && this->skybox->GetFollowCamera() == true)
	{
		return;
	}

	glm::mat4x3 controlPoints = glm::mat4x3(
		this->bezierControlPoints[0],
		this->bezierControlPoints[1],
		this->bezierControlPoints[2],
		this->bezierControlPoints[3]
	);
	
	this->selectedObject->GetTransformation()->AddComponent(new BezierCurve(controlPoints, 0.001f), true);
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

	Material* woodMaterial = new Material(0.6f, 0.8f, 0.2f, 32);

	Texture* woodTexture = new Texture();
	woodTexture->Load2DTexture("textures/wooden_fence.png");

	DrawableObjectOBJ* loginObject = new DrawableObjectOBJ(loginShader, loginModel, woodMaterial, woodTexture);
	loginObject->GetTransformation()->AddComponent(new Translate(position));

	this->objects.push_back(loginObject);

	loginObject->SetObjectID(this->objects.size() - 1);

	this->selectedObject = loginObject;
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

void Scene::ResetBezeirControlPoints()
{
	this->bezierControlPoints.clear();
}

glm::vec3 Scene::GetSelectedPosition()
{
	return this->selectedPosition;
}
