#include "SceneMaker.h"

SceneMaker::SceneMaker(float width, float height, float ratio)
{
	this->currentSceneIndex = 0;

	this->width = width;

	this->height = height;

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

		shader->SetNumberOfLights((int)lights.size());
	}

	for (auto& light : lights) {
		for (auto& shader : shaders) {
			light->AddObserver(shader);
		}
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
	Scene* scene = new Scene();

	Camera* camera = new Camera(glm::vec3(10.0f, 10.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 30.0f, 60.0f, this->width, this->height, this->ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	vector<Light*> lights;

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f, 0.75f, glm::vec3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f, 1);

	lights.push_back(light);

	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	glm::vec3 objectColor = glm::vec3(0.0f, 0.0f, 1.0f);

	Material* metalMaterial = new Material(0.1f, 0.5f, 0.9f, 32);

	float triangle[] = {
		0.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f,
		0.5f, 1.0f, 0.0f
	};

	//Init Models for Scene
	Model* triangleModel = new Model();
	triangleModel->GenerateModel(triangle, sizeof(triangle));

	//Init Shaders for Scene
	ShaderProgram* triangleShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(triangle) / sizeof(float) / 3);
	triangleShader->AddShadersFromFiles("VertexShader.glsl", "ConstantShader.glsl");


	//Init Observers for Camera
	InitObservers(camera, lights, { triangleShader });

	DrawableObject* triangleObject = new DrawableObject(triangleShader, triangleModel, objectColor, metalMaterial);
	triangleObject->GetTransformation()->AddComponent(new Scale(glm::vec3(20.0f)));

	scene->AddObject(triangleObject);

	scene->Init(camera, lights);

	AddScene(scene);
}

void SceneMaker::CreateSceneFourSpheresLight() {
	
	Scene* scene = new Scene();

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, this->width, this->height, this->ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	vector<Light*> lights;

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f), 1.25f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	lights.push_back(light);

	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);

	Material* metalMaterial = new Material(0.1f, 0.5f, 0.9f, 32);

	//Init Shaders for Scene
	vector<ShaderProgram*> shaders;

	ShaderProgram* sphereShaderPhong = new ShaderProgram(GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float) / 6);
	sphereShaderPhong->AddShadersFromFiles("VertexShader.glsl", "PhongShader.glsl");
	shaders.push_back(sphereShaderPhong);

	ShaderProgram* sphereShaderConstant = new ShaderProgram(GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float) / 6);
	sphereShaderConstant->AddShadersFromFiles("VertexShader.glsl", "ConstantShader.glsl");
	shaders.push_back(sphereShaderConstant);

	ShaderProgram* sphereShaderBlinn = new ShaderProgram(GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float) / 6);
	sphereShaderBlinn->AddShadersFromFiles("VertexShader.glsl", "BlinnPhongShader.glsl");
	shaders.push_back(sphereShaderBlinn);

	ShaderProgram* sphereShaderLambert = new ShaderProgram(GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float) / 6);
	sphereShaderLambert->AddShadersFromFiles("VertexShader.glsl", "LambertShader.glsl");
	shaders.push_back(sphereShaderLambert);

	//Init Observers for Camera
	this->InitObservers(camera, lights, shaders);

	//Init Models for Scene
	Model* sphereModel = new Model();
	sphereModel->GenerateModelWithNormal(sphere, sizeof(sphere));

	DrawableObject* sphereObject = new DrawableObject(sphereShaderPhong, sphereModel, objectColor, metalMaterial);
	sphereObject->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f)));
	sphereObject->GetTransformation()->AddComponent(new Translate(glm::vec3(- 3.0f, 0.0f, 0.0f)));

	scene->AddObject(sphereObject);

	DrawableObject* sphereObject2 = new DrawableObject(sphereShaderConstant, sphereModel, objectColor, metalMaterial);
	sphereObject2->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f)));
	sphereObject2->GetTransformation()->AddComponent(new Translate(glm::vec3(3.0f, 0.0f, 0.0f)));

	scene->AddObject(sphereObject2);

	DrawableObject* sphereObject3 = new DrawableObject(sphereShaderBlinn, sphereModel, objectColor, metalMaterial);
	sphereObject3->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f)));
	sphereObject3->GetTransformation()->AddComponent(new Translate(glm::vec3(0.0f, 3.0f, 0.0f)));
	

	scene->AddObject(sphereObject3);

	DrawableObject* sphereObject4 = new DrawableObject(sphereShaderLambert, sphereModel, objectColor, metalMaterial);
	sphereObject4->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f)));
	sphereObject4->GetTransformation()->AddComponent(new Translate(glm::vec3(0.0f, -3.0f, 0.0f)));

	scene->AddObject(sphereObject4);

	scene->Init(camera, lights);

	this->AddScene(scene);
}


void SceneMaker::CreateSceneWithMoreModels() {
	Scene* scene = new Scene();
	
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, this->width, this->height, this->ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	vector<Light*> lights;	

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.25f, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	lights.push_back(light);

	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);

	Material* metalMaterial = new Material(0.1f, 0.5f, 0.9f, 32);


	//Init Shaders for Scene
	vector<ShaderProgram*> shaders;

	ShaderProgram* giftShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(gift) / sizeof(float) / 6);
	giftShader->AddShadersFromFiles("VertexShader.glsl", "BlinnPhongShader.glsl");
	shaders.push_back(giftShader);

	ShaderProgram* suziFlatShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(suziFlat) / sizeof(float) / 6);
	suziFlatShader->AddShadersFromFiles("VertexShader.glsl", "LambertShader.glsl");
	shaders.push_back(suziFlatShader);

	ShaderProgram* suziSmoothShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(suziSmooth) / sizeof(float) / 6);
	suziSmoothShader->AddShadersFromFiles("VertexShader.glsl", "PhongShader.glsl");
	shaders.push_back(suziSmoothShader);

	ShaderProgram* sphereShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(sphere) / sizeof(float) / 6);
	sphereShader->AddShadersFromFiles("VertexShader.glsl", "ConstantShader.glsl");
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
	giftObject->GetTransformation()->AddComponent(new Scale(glm::vec3(1.5f, 1.5f, 1.5f)));
	giftObject->GetTransformation()->AddComponent(new Translate(glm::vec3(-3.0f, 0.0f, 0.0f)));

	scene->AddObject(giftObject);

	DrawableObject* suziFlatObject = new DrawableObject(suziFlatShader, suziFlatModel, objectColor, metalMaterial);
	suziFlatObject->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	suziFlatObject->GetTransformation()->AddComponent(new Translate(glm::vec3(3.0f, 0.0f, 0.0f)));

	scene->AddObject(suziFlatObject);

	DrawableObject* suziSmoothObject = new DrawableObject(suziSmoothShader, suziFlatModel, objectColor, metalMaterial);
	suziSmoothObject->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	suziSmoothObject->GetTransformation()->AddComponent(new Translate(glm::vec3(0.0f, 3.0f, 0.0f)));

	scene->AddObject(suziSmoothObject);

	DrawableObject* sphereObject = new DrawableObject(sphereShader, sphereModel, objectColor, metalMaterial);
	sphereObject->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f)));
	sphereObject->GetTransformation()->AddComponent(new Translate(glm::vec3(0.0f, -3.0f, 0.0f)));

	scene->AddObject(sphereObject);

	scene->Init(camera, lights);

	this->AddScene(scene);
}

void SceneMaker::CreateSceneForest()
{
	Scene* scene = new Scene();

	Camera* camera = new Camera(glm::vec3(0.0f, 10.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, this->width, this->height, this->ratio, 0.1f, 100.0f);

	camera->Rotate(0.0f, -45.0f);

	vector<Light*> lights;

	Light* light = new Light(glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f), 10.0f, 0.125f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	Light* light2 = new Light(glm::vec3(0.0f, 0.2f, 15.0f), glm::vec3(0.3f, 0.3f, 0.3f), 10.0f, 0.125f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	Light* light3 = new Light(glm::vec3(15.0f, 0.2f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f), 10.0f, 0.125f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	Light* light4 = new Light(glm::vec3(15.0f, 0.2f, 15.0f), glm::vec3(0.3f, 0.3f, 0.3f), 10.0f, 0.125f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1);

	Light* light5 = new Light(glm::vec3(7.5f, 0.2f, 7.5f), glm::vec3(0.3f, 0.3f, 0.3f), 0.5f, 0.125f, glm::vec3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f, 3);

	lights.push_back(light);

	lights.push_back(light2);

	lights.push_back(light3);

	lights.push_back(light4);

	lights.push_back(light5);

	Light* spotLight = new Light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.5f, glm::vec3(0.0f, 0.0f, 1.0f), 6.5f, 20.5f, 2);

	lights.push_back(spotLight);

	camera->AddObserver(spotLight);

	//Light* dirLight = new Light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.05f, glm::vec3(0.0f, 0.0f, 1.0f), 6.5f, 17.5f, 3);
	//Light* dirLight2 = new Light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.05f, glm::vec3(0.0f, -1.0f, 0.0f), 6.5f, 17.5f, 3);

	//lights.push_back(dirLight);	
	//lights.push_back(dirLight2);

	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	//Init objectColor for Scene Trees, Bushes
	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);

	//Init Material for Scene Trees, Bushes
	Material* woodMaterial = new Material(0.6f, 0.8f, 0.2f, 32);
	Material* soilMaterial = new Material(0.5f, 0.7f, 0.1f, 32);
	Material* bushMaterial = new Material(0.6f, 0.8f, 0.15f, 32);

	//Init Models for Scene Trees, Bushes
	ModelObject* treeModel = new ModelObject();
	treeModel->GenerateModelFromOBJ("objects/tree.obj");

	Model* bushModel = new Model();
	bushModel->GenerateModelWithNormal(bushes, sizeof(bushes));

	ModelObject* plainModel = new ModelObject();
	plainModel->GenerateModelFromOBJ("objects/teren.obj");

	ModelObject* houseModel = new ModelObject();
	houseModel->GenerateModelFromOBJ("objects/house.obj");

	ModelObject* cokeModel = new ModelObject();
	cokeModel->GenerateModelFromOBJ("objects/coke.obj");

	ModelObject* loginModel = new ModelObject();
	loginModel->GenerateModelFromOBJ("objects/login.obj");

	ModelObject* zombieModel = new ModelObject();
	zombieModel->GenerateModelFromOBJ("objects/zombie.obj");

	Model* skyboxModel = new Model();
	skyboxModel->GenerateModel(skycube, sizeof(skycube));

	//Init Shaders for Scene Trees, Bushes
	vector<ShaderProgram*> shaders;

	ShaderProgram* treeShader = new ShaderProgram(GL_TRIANGLES, 0, treeModel->GetIndicesCount());
	treeShader->AddShadersFromFiles("VertexShader.glsl", "PhongShader.glsl");
	shaders.push_back(treeShader);

	ShaderProgram* bushShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float) / 6);
	bushShader->AddShadersFromFiles("VertexShader.glsl", "BlinnPhongShader.glsl");
	shaders.push_back(bushShader);

	ShaderProgram* plainShader = new ShaderProgram(GL_TRIANGLES, 0, plainModel->GetIndicesCount());
	plainShader->AddShadersFromFiles("VertexShader.glsl", "LambertShader.glsl");
	shaders.push_back(plainShader);

	ShaderProgram* houseShader = new ShaderProgram(GL_TRIANGLES, 0, houseModel->GetIndicesCount());
	houseShader->AddShadersFromFiles("VertexShader.glsl", "PhongShader.glsl");
	shaders.push_back(houseShader);

	ShaderProgram* cokeShader = new ShaderProgram(GL_TRIANGLES, 0, cokeModel->GetIndicesCount());
	cokeShader->AddShadersFromFiles("VertexShader.glsl", "BlinnPhongShader.glsl");
	shaders.push_back(cokeShader);

	ShaderProgram* loginshader = new ShaderProgram(GL_TRIANGLES, 0, loginModel->GetIndicesCount());
	loginshader->AddShadersFromFiles("VertexShader.glsl", "PhongShader.glsl");
	shaders.push_back(loginshader);

	ShaderProgram* zombieShader = new ShaderProgram(GL_TRIANGLES, 0, zombieModel->GetIndicesCount());
	zombieShader->AddShadersFromFiles("VertexShader.glsl", "PhongShader.glsl");
	shaders.push_back(zombieShader);

	ShaderProgram* skyboxShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(skycube) / sizeof(float) / 3);
	skyboxShader->AddShadersFromFiles("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	shaders.push_back(skyboxShader);

	//Init Observers for Camera
	this->InitObservers(camera, lights, shaders);

	//Init Textures for Scene
	Texture* plainTexture = new Texture();
	plainTexture->Load2DTexture("textures/grass.png");

	Texture* houseTexture = new Texture();
	houseTexture->Load2DTexture("textures/house.png");

	Texture* cokeTexture = new Texture();
	cokeTexture->Load2DTexture("textures/coke_logo.jpg");

	Texture* loginTexture = new Texture();
	loginTexture->Load2DTexture("textures/wooden_fence.png");

	Texture* zombieTexture = new Texture();
	zombieTexture->Load2DTexture("textures/zombie.png");

	Texture* treeTexture = new Texture();
	treeTexture->Load2DTexture("textures/tree.png");

	Texture* cubemapTexture = new Texture();

	vector<string> filePaths = {
		"textures/posx.jpg",
		"textures/negx.jpg",
		"textures/posy.jpg",
		"textures/negy.jpg",
		"textures/posz.jpg",
		"textures/negz.jpg"
	};

	cubemapTexture->LoadCubemap(filePaths);
	

	//Scene Forest
	DrawableObjectOBJ* plainObject = new DrawableObjectOBJ(plainShader, plainModel, soilMaterial, plainTexture);
	plainObject->GetTransformation()->AddComponent(new Scale(glm::vec3(0.8f)));
	plainObject->GetTransformation()->AddComponent(new Translate(glm::vec3(0.45f, 0.0f, 0.5f)));

	scene->AddObject(plainObject);

	DrawableObjectOBJ* houseObject = new DrawableObjectOBJ(houseShader, houseModel, woodMaterial, houseTexture);

	houseObject->GetTransformation()->AddComponent(new Translate(glm::vec3(10.0f, 0.0f, 25.0f)));
	houseObject->GetTransformation()->AddComponent(new Rotate(glm::vec3(0.0f, 90.0f, 0.0f)));
	houseObject->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f)));

	scene->AddObject(houseObject);

	DrawableObjectOBJ* cokeObject = new DrawableObjectOBJ(cokeShader, cokeModel, woodMaterial, cokeTexture);

	cokeObject->GetTransformation()->AddComponent(new Scale(glm::vec3(0.5f)));
	cokeObject->GetTransformation()->AddComponent(new Translate(glm::vec3(-5.0f, 0.0f, 0.0f)));

	scene->AddObject(cokeObject);

	DrawableObjectOBJ* loginObject = new DrawableObjectOBJ(loginshader, loginModel, woodMaterial, loginTexture);

	loginObject->GetTransformation()->AddComponent(new Scale(glm::vec3(2.0f)));
	loginObject->GetTransformation()->AddComponent(new Translate(glm::vec3(0.0f, 2.0f, 0.0f)));
	
	scene->AddObject(loginObject);

	for (int i = 0; i < 10; i++) {
		DrawableObjectOBJ* zombieObject = new DrawableObjectOBJ(zombieShader, zombieModel, woodMaterial, zombieTexture);

		zombieObject->GetTransformation()->AddComponent(new Translate(glm::vec3(0.0f + i * 2, 0.05f, -10.0f)));
		zombieObject->GetTransformation()->AddComponent(new Scale(glm::vec3(1.0f)));

		scene->AddObject(zombieObject);
	}

	for (int i = 0; i < 10; i++) {
		DrawableObjectOBJ* zombieObject = new DrawableObjectOBJ(zombieShader, zombieModel, woodMaterial, zombieTexture);

		zombieObject->GetTransformation()->AddComponent(new Translate(glm::vec3(0.0f + i * 2, 0.05f, -8.0f)));
		zombieObject->GetTransformation()->AddComponent(new Scale(glm::vec3(1.0f)));

		scene->AddObject(zombieObject);
	}

	srand((unsigned int)(time(NULL)));

	const int gridRows = 20;
	const int gridCols = 20;
	const float spacing = 15.0f;

	for (int row = 0; row < gridRows; row++) {
		for (int col = 0; col < gridCols; col++) {
			float xPos = col * spacing;
			float yPos = 0.0f;
			float zPos = row * spacing;

			DrawableObjectOBJ* treeObject = new DrawableObjectOBJ(treeShader, treeModel, woodMaterial, treeTexture);

			treeObject->GetTransformation()->AddComponent(new Scale(glm::vec3((float)(rand() % 100 / 5000.0 + 0.05f))));
			treeObject->GetTransformation()->AddComponent(new Translate(glm::vec3(xPos, yPos, zPos)));

			float randomAngleY = (float)(rand() % 360);
			float randomAngleX = (float)(rand() % 40 - 20);

			treeObject->GetTransformation()->AddComponent(new Rotate(glm::vec3(randomAngleX, randomAngleY, 0.0f)));

			if (rand() % 100 < 30) {
				treeObject->GetTransformation()->AddComponent(new DynamicRotate(glm::vec3(0.0f), glm::vec3(0.0f, 20.0f, 0.0f), 0.01f));
			}

			scene->AddObject(treeObject);

			DrawableObject* bushObject = new DrawableObject(bushShader, bushModel, objectColor, bushMaterial);

			bushObject->GetTransformation()->AddComponent(new Scale(glm::vec3((float)(rand() % 100 / 500.0 + 0.05f))));
			bushObject->GetTransformation()->AddComponent(new Translate(glm::vec3(xPos * 0.35f, yPos, zPos * 0.35f)));

			scene->AddObject(bushObject);
		}
	}

	Skybox* skyboxObject = new Skybox(skyboxShader, skyboxModel, soilMaterial, cubemapTexture);

	scene->SetSkybox(skyboxObject);

	scene->Init(camera, lights);

	this->AddScene(scene);
}

void SceneMaker::CreateSceneForestDark()
{
	Scene* scene = new Scene();
	
	Camera* camera = new Camera(glm::vec3(0.0f, 10.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, this->width, this->height, this->ratio, 0.1f, 100.0f);

	camera->Rotate(0.0f, -45.0f);

	vector<Light*> lights;

	Light* light = new Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.05f, glm::vec3(0.0f, 0.0f, 0.0f), 6.5f, 17.5f, 2);
	
	lights.push_back(light);
	
	for (int i = 0; i < lights.size(); i++) {
		lights[i]->SetIndex(i);
	}

	camera->AddObserver(light);

	//Init objectColor for Scene Trees, Bushes
	glm::vec3 objectColor = glm::vec3(0.385f, 0.647f, 0.812f);

	//Init Material for Scene Trees, Bushes
	Material* woodMaterial = new Material(0.6f, 0.8f, 0.2f, 32);
	Material* soilMaterial = new Material(0.5f, 0.7f, 0.1f, 32);
	Material* bushMaterial = new Material(0.6f, 0.8f, 0.15f, 32);

	//Init Shaders for Scene Trees, Bushes
	vector<ShaderProgram*> shaders;

	ShaderProgram* treeShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(tree) / sizeof(float) / 6);
	treeShader->AddShadersFromFiles("VertexShader.glsl", "LambertShader.glsl");
	shaders.push_back(treeShader);

	ShaderProgram* bushShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float) / 6);
	bushShader->AddShadersFromFiles("VertexShader.glsl", "LambertShader.glsl");
	shaders.push_back(bushShader);

	ShaderProgram* plainShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(plain) / sizeof(float) / 6);
	plainShader->AddShadersFromFiles("VertexShader.glsl", "LambertShader.glsl");
	shaders.push_back(plainShader);

	//Init Models for Scene Trees, Bushes
	Model* treeModel = new Model();
	treeModel->GenerateModelWithNormal(tree, sizeof(tree));

	Model* bushModel = new Model();
	bushModel->GenerateModelWithNormal(bushes, sizeof(bushes));

	Model* plainModel = new Model();
	plainModel->GenerateModelWithNormalAndUV(plain, sizeof(plain));

	//Init Observers for Camera
	this->InitObservers(camera, lights, shaders);

	//Init Textures for Scene
	Texture* plainTexture = new Texture();

	plainTexture->Load2DTexture("textures/grass.png");

	//Scene Forest
	DrawableObject* plainObject = new DrawableObject(plainShader, plainModel, soilMaterial, plainTexture);
	plainObject->GetTransformation()->AddComponent(new Scale(glm::vec3(25.0f)));
	plainObject->GetTransformation()->AddComponent(new Translate(glm::vec3(0.45f, 0.0f, 0.5f)));

	scene->AddObject(plainObject);

	srand((unsigned int)(time(NULL)));

	const int gridRows = 30;
	const int gridCols = 30;
	const float spacing = 5.0f;


	for (int row = 0; row < gridRows; row++) {
		for (int col = 0; col < gridCols; col++) {
			float xPos = col * spacing;
			float yPos = 0.0f;
			float zPos = row * spacing;

			DrawableObject* treeObject = new DrawableObject(treeShader, treeModel, objectColor, woodMaterial);

			treeObject->GetTransformation()->AddComponent(new Scale(glm::vec3((float)(rand() % 100 / 1000.0 + 0.05f))));
			treeObject->GetTransformation()->AddComponent(new Translate(glm::vec3(xPos, yPos, zPos)));

			float randomAngleY = (float)(rand() % 360);
			float randomAngleX = (float)(rand() % 40 - 20);

			treeObject->GetTransformation()->AddComponent(new Rotate(glm::vec3(randomAngleX, randomAngleY, 0.0f)));

			if (rand() % 100 < 30) { 
				treeObject->GetTransformation()->AddComponent(new DynamicRotate(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f), 0.01f));
			}

			scene->AddObject(treeObject);

			DrawableObject* bushObject = new DrawableObject(bushShader, bushModel, objectColor, bushMaterial);

			bushObject->GetTransformation()->AddComponent(new Scale(glm::vec3((float)(rand() % 100 / 500.0 + 0.05f))));
			bushObject->GetTransformation()->AddComponent(new Translate(glm::vec3(xPos - 5, yPos, zPos + spacing * 0.25f)));

			scene->AddObject(bushObject);
		}
	}


	scene->Init(camera, lights);

	this->AddScene(scene);
}
