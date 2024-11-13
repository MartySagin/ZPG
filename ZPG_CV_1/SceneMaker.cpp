#include "SceneMaker.h"

SceneMaker::SceneMaker(float ratio)
{
	this->currentSceneIndex = 0;

	this->ratio = ratio;
}

void SceneMaker::AddScene(Scene* scene)
{
	this->scenes.push_back(scene);

}

void SceneMaker::SwitchScene()
{
	this->currentSceneIndex++;

	if (this->currentSceneIndex >= this->scenes.size())
	{
		this->currentSceneIndex = 0;
	}

}

void SceneMaker::InitObservers(Camera* camera, vector<Light*> lights, vector<ShaderProgram*> shaders)
{
	for (auto& shader : shaders) {
		camera->AddObserver(shader);
	}

	for (auto& light : lights) {
		for (auto& shader : shaders) {
			light->AddObserver(shader);
		}
	}

	for (auto& shader : shaders) {
		shader->SetNumberOfLights(lights.size());
	}
}

Scene* SceneMaker::GetCurrentScene()
{
	return this->scenes[this->currentSceneIndex];
}

vector<Scene*> SceneMaker::GetAllScenes()
{
	return this->scenes;
}

void SceneMaker::CreateSceneTriangle()
{
	vector<DrawableObject*> objects;
	
	Camera* camera = new Camera(glm::vec3(10.0f, 10.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 30.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	vector<Light*> lights(0);

	glm::vec3 objectColor = glm::vec3(0.0f, 0.0f, 1.0f);

	Material* metalMaterial = new Material(0.1f, 0.5f, 0.9f);

	float triangle[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.5f, 1.0f, 0.0f
	};

	//Init Shaders for Scene
	ShaderProgram* triangleShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(triangle) / sizeof(float) / 3);
	triangleShader->AddShadersFromFiles("VertexShader.txt", "ConstantShader.txt");

	//Init Models for Scene
	Model* triangleModel = new Model();
	triangleModel->GenerateModel(triangle, sizeof(triangle));

	//Init Observers for Camera
	camera->AddObserver(triangleShader);

	DrawableObject* triangleObject = new DrawableObject(triangleShader, triangleModel, objectColor, metalMaterial);
	triangleObject->GetTransformation()->AddComponent(new Scale(20.0f));

	objects.push_back(triangleObject);

	Scene* scene = new Scene();

	scene->Init(objects, camera, lights);

	AddScene(scene);
}

void SceneMaker::CreateSceneFourSpheresLight() {
	vector<DrawableObject*> objects;

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	vector<Light*> lights;

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.25f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	lights.push_back(light);

	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);

	Material* metalMaterial = new Material(0.1f, 0.5f, 0.9f);

	//Init Shaders for Scene
	ShaderProgram* sphereShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float) / 6);
	sphereShader->AddShadersFromFiles("VertexShader.txt", "PhongShader.txt");

	//Init Observers for Camera
	camera->AddObserver(sphereShader);

	light->AddObserver(sphereShader);

	sphereShader->SetNumberOfLights(lights.size());

	//Init Models for Scene
	Model* sphereModel = new Model();
	sphereModel->GenerateModelWithNormal(sphere, sizeof(sphere));

	DrawableObject* sphereObject = new DrawableObject(sphereShader, sphereModel, objectColor, metalMaterial);
	sphereObject->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject->GetTransformation()->AddComponent(new Translate(-3.0f, 0.0f, 0.0f));

	objects.push_back(sphereObject);

	DrawableObject* sphereObject2 = new DrawableObject(sphereShader, sphereModel, objectColor, metalMaterial);
	sphereObject2->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject2->GetTransformation()->AddComponent(new Translate(3.0f, 0.0f, 0.0f));

	objects.push_back(sphereObject2);

	DrawableObject* sphereObject3 = new DrawableObject(sphereShader, sphereModel, objectColor, metalMaterial);
	sphereObject3->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject3->GetTransformation()->AddComponent(new Translate(0.0f, 3.0f, 0.0f));

	objects.push_back(sphereObject3);

	DrawableObject* sphereObject4 = new DrawableObject(sphereShader, sphereModel, objectColor, metalMaterial);
	sphereObject4->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject4->GetTransformation()->AddComponent(new Translate(0.0f, -3.0f, 0.0f));

	objects.push_back(sphereObject4);

	Scene* scene = new Scene();

	scene->Init(objects, camera, lights);

	this->AddScene(scene);
}


void SceneMaker::CreateSceneWithMoreModels() {
	vector<DrawableObject*> objects;
	
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	vector<Light*> lights;	

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.25f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	lights.push_back(light);

	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);

	Material* metalMaterial = new Material(0.1f, 0.5f, 0.9f);


	//Init Shaders for Scene
	vector<ShaderProgram*> shaders;

	ShaderProgram* giftShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(gift) / sizeof(float) / 6);
	giftShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");
	shaders.push_back(giftShader);

	ShaderProgram* suziFlatShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(suziFlat) / sizeof(float) / 6);
	suziFlatShader->AddShadersFromFiles("VertexShader.txt", "LambertShader.txt");
	shaders.push_back(suziFlatShader);

	ShaderProgram* suziSmoothShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(suziSmooth) / sizeof(float) / 6);
	suziSmoothShader->AddShadersFromFiles("VertexShader.txt", "PhongShader.txt");
	shaders.push_back(suziSmoothShader);

	ShaderProgram* sphereShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float) / 6);
	sphereShader->AddShadersFromFiles("VertexShader.txt", "ConstantShader.txt");
	shaders.push_back(sphereShader);


	//Init Observers for Camera
	this->InitObservers(camera, lights, shaders);

	//Init Models for Scene
	Model* giftModel = new Model();
	giftModel->GenerateModelWithNormal(gift, sizeof(gift));

	Model* suziFlatModel = new Model();
	suziFlatModel->GenerateModelWithNormal(suziFlat, sizeof(suziFlat));

	Model* suziSmoothModel = new Model();
	suziSmoothModel->GenerateModelWithNormal(suziSmooth, sizeof(suziSmooth));

	Model* sphereModel = new Model();
	sphereModel->GenerateModelWithNormal(sphere, sizeof(sphere));


	DrawableObject* giftObject = new DrawableObject(giftShader, giftModel, objectColor, metalMaterial);
	giftObject->GetTransformation()->AddComponent(new Scale(1.5f));
	giftObject->GetTransformation()->AddComponent(new Translate(-3.0f, 0.0f, 0.0f));

	objects.push_back(giftObject);

	DrawableObject* suziFlatObject = new DrawableObject(suziFlatShader, suziFlatModel, objectColor, metalMaterial);
	suziFlatObject->GetTransformation()->AddComponent(new Scale(0.5f));
	suziFlatObject->GetTransformation()->AddComponent(new Translate(3.0f, 0.0f, 0.0f));

	objects.push_back(suziFlatObject);

	DrawableObject* suziSmoothObject = new DrawableObject(suziSmoothShader, suziFlatModel, objectColor, metalMaterial);
	suziSmoothObject->GetTransformation()->AddComponent(new Scale(0.5f));
	suziSmoothObject->GetTransformation()->AddComponent(new Translate(0.0f, 3.0f, 0.0f));

	objects.push_back(suziSmoothObject);

	DrawableObject* sphereObject = new DrawableObject(sphereShader, sphereModel, objectColor, metalMaterial);
	sphereObject->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject->GetTransformation()->AddComponent(new Translate(0.0f, -3.0f, 0.0f));

	objects.push_back(sphereObject);

	Scene* scene = new Scene();

	scene->Init(objects, camera, lights);

	this->AddScene(scene);
}

void SceneMaker::CreateSceneForest()
{
	vector<DrawableObject*> objects;

	Camera* camera = new Camera(glm::vec3(0.0f, 10.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(0.0f, -45.0f);

	vector<Light*> lights;

	Light* light = new Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);
	Light* light2 = new Light(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);
	Light* light3 = new Light(glm::vec3(15.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);
	Light* light4 = new Light(glm::vec3(15.0f, 5.0f, 15.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	lights.push_back(light);

	lights.push_back(light2);

	lights.push_back(light3);

	lights.push_back(light4);

	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);


	//Init Material for Scene Trees, Bushes
	Material* woodMaterial = new Material(0.6f, 0.8f, 0.2f);
	Material* soilMaterial = new Material(0.5f, 0.7f, 0.1f);
	Material* bushMaterial = new Material(0.6f, 0.8f, 0.15f);

	srand((unsigned int)(time(NULL)));

	const int gridRows = 30;
	const int gridCols = 30;
	const float spacing = 5.0f;

	//Init Shaders for Scene Trees, Bushes
	vector<ShaderProgram*> shaders;

	ShaderProgram* treeShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(tree) / sizeof(float) / 6);
	treeShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");
	shaders.push_back(treeShader);

	ShaderProgram* bushShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float) / 6);
	bushShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");
	shaders.push_back(bushShader);

	ShaderProgram* plainShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(plain) / sizeof(float) / 6);
	plainShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");
	shaders.push_back(plainShader);

	//Init Models for Scene Trees, Bushes
	Model* treeModel = new Model();
	treeModel->GenerateModelWithNormal(tree, sizeof(tree));

	Model* bushModel = new Model();
	bushModel->GenerateModelWithNormal(bushes, sizeof(bushes));

	Model* plainModel = new Model();
	plainModel->GenerateModelWithNormal(plain, sizeof(plain));

	//Init Observers for Camera
	this->InitObservers(camera, lights, shaders);

	//Scene Forest
	DrawableObject* plainObject = new DrawableObject(plainShader, plainModel, glm::vec3(0.0f, 1.0f, 0.0f), soilMaterial);
	plainObject->GetTransformation()->AddComponent(new Scale(25.0f));
	plainObject->GetTransformation()->AddComponent(new Translate(0.45f, 0.0f, 0.5f));

	objects.push_back(plainObject);

	Scene* scene = new Scene();

	for (int row = 0; row < gridRows; row++) {
		for (int col = 0; col < gridCols; col++) {
			float xPos = col * spacing;
			float yPos = 0.0f;
			float zPos = row * spacing;

			//DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), GL_TRIANGLES, "VertexShader.txt", "BlinnPhongShader.txt", camera, light, true);
			DrawableObject* treeObject = new DrawableObject(treeShader, treeModel, objectColor, woodMaterial);

			treeObject->GetTransformation()->AddComponent(new Scale((float)(rand() % 100 / 1000.0 + 0.05f)));
			treeObject->GetTransformation()->AddComponent(new Translate(xPos, yPos, zPos));

			float randomAngleY = (float)(rand() % 360);
			float randomAngleX = (float)(rand() % 40 - 20);

			treeObject->GetTransformation()->AddComponent(new Rotate(randomAngleX, randomAngleY, 0.0f));

			if (rand() % 100 < 30) {

				scene->AddAnimation([treeObject](float deltaTime) {

					treeObject->GetTransformation()->AddComponent(new Rotate(0.0f, 20.0f * deltaTime, 0.0f));

				});

			}

			objects.push_back(treeObject);

			//DrawableObject* bushObject = new DrawableObject(bushes, sizeof(bushes), GL_TRIANGLES, "VertexShader.txt", "BlinnPhongShader.txt", camera, light, true);
			DrawableObject* bushObject = new DrawableObject(bushShader, bushModel, objectColor, bushMaterial);

			bushObject->GetTransformation()->AddComponent(new Scale((float)(rand() % 100 / 500.0 + 0.05f)));
			bushObject->GetTransformation()->AddComponent(new Translate(xPos - 5, yPos, zPos + spacing * 0.25f));

			objects.push_back(bushObject);
		}
	}

	scene->AddAnimation([lights](float deltaTime) {
		static float time = 0.0f;

		time += deltaTime;

		for (auto& light : lights) {

			float angleOffset = glm::linearRand(0.0f, 6.28318f);

			float speed = 5.0f;
			float radius = 2.0f;

			float x = radius * cos(time * speed + angleOffset);
			float z = radius * sin(time * speed + angleOffset);

			glm::vec3 newPosition = light->GetPosition() + glm::vec3(x, 0.0f, z) * deltaTime;

			light->SetPosition(newPosition);
		}
	});


	scene->Init(objects, camera, lights);

	this->AddScene(scene);
}

void SceneMaker::CreateSceneForestDark()
{
	vector<DrawableObject*> objects;
	
	Camera* camera = new Camera(glm::vec3(0.0f, 10.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(0.0f, -45.0f);

	vector<Light*> lights;

	Light* light = new Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.05f, glm::vec3(0.0f, 0.0f, 0.0f), 6.5f, 17.5f, 2);
	
	lights.push_back(light);
	
	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	camera->AddObserver(light);

	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);

	//Init Material for Scene Trees, Bushes
	Material* woodMaterial = new Material(0.6f, 0.8f, 0.2f);
	Material* soilMaterial = new Material(0.5f, 0.7f, 0.1f);
	Material* bushMaterial = new Material(0.6f, 0.8f, 0.15f);

	srand((unsigned int)(time(NULL)));

	const int gridRows = 30;
	const int gridCols = 30;
	const float spacing = 5.0f;

	//Init Shaders for Scene Trees, Bushes
	vector<ShaderProgram*> shaders;

	ShaderProgram* treeShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(tree) / sizeof(float) / 6);
	treeShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");
	shaders.push_back(treeShader);

	ShaderProgram* bushShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float) / 6);
	bushShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");
	shaders.push_back(bushShader);

	ShaderProgram* plainShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(plain) / sizeof(float) / 6);
	plainShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");
	shaders.push_back(plainShader);

	//Init Models for Scene Trees, Bushes
	Model* treeModel = new Model();
	treeModel->GenerateModelWithNormal(tree, sizeof(tree));

	Model* bushModel = new Model();
	bushModel->GenerateModelWithNormal(bushes, sizeof(bushes));

	Model* plainModel = new Model();
	plainModel->GenerateModelWithNormal(plain, sizeof(plain));

	//Init Observers for Camera
	this->InitObservers(camera, lights, shaders);

	//Scene Forest
	DrawableObject* plainObject = new DrawableObject(plainShader, plainModel, glm::vec3(0.0f, 1.0f, 0.0f), soilMaterial);
	plainObject->GetTransformation()->AddComponent(new Scale(25.0f));
	plainObject->GetTransformation()->AddComponent(new Translate(0.45f, 0.0f, 0.5f));

	objects.push_back(plainObject);

	Scene* scene = new Scene();

	for (int row = 0; row < gridRows; row++) {
		for (int col = 0; col < gridCols; col++) {
			float xPos = col * spacing;
			float yPos = 0.0f;
			float zPos = row * spacing;

			//DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), GL_TRIANGLES, "VertexShader.txt", "BlinnPhongShader.txt", camera, light, true);
			DrawableObject* treeObject = new DrawableObject(treeShader, treeModel, objectColor, woodMaterial);

			treeObject->GetTransformation()->AddComponent(new Scale((float)(rand() % 100 / 1000.0 + 0.05f)));
			treeObject->GetTransformation()->AddComponent(new Translate(xPos, yPos, zPos));

			float randomAngleY = (float)(rand() % 360);
			float randomAngleX = (float)(rand() % 40 - 20);

			treeObject->GetTransformation()->AddComponent(new Rotate(randomAngleX, randomAngleY, 0.0f));

			if (rand() % 100 < 30) { 

				scene->AddAnimation([treeObject](float deltaTime) {

					treeObject->GetTransformation()->AddComponent(new Rotate(0.0f, 20.0f * deltaTime, 0.0f));

				});

			}

			objects.push_back(treeObject);

			//DrawableObject* bushObject = new DrawableObject(bushes, sizeof(bushes), GL_TRIANGLES, "VertexShader.txt", "BlinnPhongShader.txt", camera, light, true);
			DrawableObject* bushObject = new DrawableObject(bushShader, bushModel, objectColor, bushMaterial);

			bushObject->GetTransformation()->AddComponent(new Scale((float)(rand() % 100 / 500.0 + 0.05f)));
			bushObject->GetTransformation()->AddComponent(new Translate(xPos - 5, yPos, zPos + spacing * 0.25f));

			objects.push_back(bushObject);
		}
	}


	scene->Init(objects, camera, lights);

	this->AddScene(scene);
}
