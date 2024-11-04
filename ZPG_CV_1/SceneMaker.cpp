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

Scene* SceneMaker::GetCurrentScene()
{
	return this->scenes[this->currentSceneIndex];
}

void SceneMaker::CreateSceneTriangle()
{
	vector<DrawableObject*> objects;
	
	Camera* camera = new Camera(glm::vec3(10.0f, 10.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 30.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	Light* light = new Light(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 1.25f, 0.15f);

	float triangle[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.5f, 1.0f, 0.0f
	};

	VertexShader* vertexShader = new VertexShader();
	FragmentShader* fragmentShader = new FragmentShader(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	DrawableObject* triangleObject = new DrawableObject(triangle, sizeof(triangle), GL_TRIANGLES, vertexShader, fragmentShader, camera, light, false);
	triangleObject->GetTransformation()->AddComponent(new Scale(20.0f));

	objects.push_back(triangleObject);

	Scene* scene = new Scene();

	scene->Init(objects, camera, light);

	AddScene(scene);
}

void SceneMaker::CreateSceneFourSpheresLight() {
	vector<DrawableObject*> objects;

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 1.25f, 0.15f);

	DrawableObject* sphereObject = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "VertexShader.txt", "PhongShader.txt", camera, light, true);
	sphereObject->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject->GetTransformation()->AddComponent(new Translate(-3.0f, 0.0f, 0.0f));

	objects.push_back(sphereObject);

	DrawableObject* sphereObject2 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "VertexShader.txt", "PhongShader.txt", camera, light, true);
	sphereObject2->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject2->GetTransformation()->AddComponent(new Translate(3.0f, 0.0f, 0.0f));

	objects.push_back(sphereObject2);

	DrawableObject* sphereObject3 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "VertexShader.txt", "PhongShader.txt", camera, light, true);
	sphereObject3->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject3->GetTransformation()->AddComponent(new Translate(0.0f, 3.0f, 0.0f));

	objects.push_back(sphereObject3);

	DrawableObject* sphereObject4 = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "VertexShader.txt", "PhongShader.txt", camera, light, true);
	sphereObject4->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject4->GetTransformation()->AddComponent(new Translate(0.0f, -3.0f, 0.0f));

	objects.push_back(sphereObject4);

	Scene* scene = new Scene();

	scene->Init(objects, camera, light);

	this->AddScene(scene);
}


void SceneMaker::CreateSceneWithMoreModels() {
	vector<DrawableObject*> objects;
	
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(-90.0f, 0.0f);

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 1.25f, 0.15f);

	DrawableObject* giftObject = new DrawableObject(gift, sizeof(gift), GL_TRIANGLES, "VertexShader.txt", "BlinnPhongShader.txt", camera, light, true);
	giftObject->GetTransformation()->AddComponent(new Scale(1.5f));
	giftObject->GetTransformation()->AddComponent(new Translate(-3.0f, 0.0f, 0.0f));

	objects.push_back(giftObject);

	DrawableObject* suziFlatObject = new DrawableObject(suziFlat, sizeof(suziFlat), GL_TRIANGLES, "VertexShader.txt", "PhongShader.txt", camera, light, true);
	suziFlatObject->GetTransformation()->AddComponent(new Scale(0.5f));
	suziFlatObject->GetTransformation()->AddComponent(new Translate(3.0f, 0.0f, 0.0f));

	objects.push_back(suziFlatObject);

	DrawableObject* suziSmoothObject = new DrawableObject(suziSmooth, sizeof(suziSmooth), GL_TRIANGLES, "VertexShader.txt", "LambertShader.txt", camera, light, true);
	suziSmoothObject->GetTransformation()->AddComponent(new Scale(0.5f));
	suziSmoothObject->GetTransformation()->AddComponent(new Translate(0.0f, 3.0f, 0.0f));

	objects.push_back(suziSmoothObject);

	DrawableObject* sphereObject = new DrawableObject(sphere, sizeof(sphere), GL_TRIANGLES, "VertexShader.txt", "ConstantShader.txt", camera, light, true);
	sphereObject->GetTransformation()->AddComponent(new Scale(0.5f));
	sphereObject->GetTransformation()->AddComponent(new Translate(0.0f, -3.0f, 0.0f));

	objects.push_back(sphereObject);

	Scene* scene = new Scene();

	scene->Init(objects, camera, light);

	this->AddScene(scene);
}

void SceneMaker::CreateSceneForest()
{
	vector<DrawableObject*> objects;
	
	Camera* camera = new Camera(glm::vec3(0.0f, 10.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 60.0f, ratio, 0.1f, 100.0f);

	camera->Rotate(0.0f, -45.0f);

	Light* light = new Light(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.385f, 0.647f, 0.812f), 1.0f, 0.15f);

	//Init Shaders for Scene
	FragmentShader* fragmentShaderPlain = new FragmentShader(glm::vec4(0.3f, 0.20f, 0.20f, 1.0f));

	VertexShader* vertexShaderWithNormal = new VertexShader();
	vertexShaderWithNormal->CreateNewShaderWithNormal();

	//Scene Forest
	DrawableObject* plainObject = new DrawableObject(plain, sizeof(plain), GL_TRIANGLES, vertexShaderWithNormal, fragmentShaderPlain, camera, light, true);
	plainObject->GetTransformation()->AddComponent(new Scale(25.0f));
	plainObject->GetTransformation()->AddComponent(new Translate(0.45f, 0.0f, 0.5f));

	objects.push_back(plainObject);

	srand(time(NULL));

	const int gridRows = 30;
	const int gridCols = 30;
	const float spacing = 5.0f;

	//Init Shaders for Scene Trees, Bushes
	ShaderProgram* treeShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(tree) / sizeof(float) / 6, camera, light);
	treeShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");

	ShaderProgram* bushShader = new ShaderProgram(GL_TRIANGLES, 0, sizeof(bushes) / sizeof(float) / 6, camera, light);
	bushShader->AddShadersFromFiles("VertexShader.txt", "BlinnPhongShader.txt");

	//Init Models for Scene Trees, Bushes
	Model* treeModel = new Model();
	treeModel->GenerateModelWithNormal(tree, sizeof(tree));

	Model* bushModel = new Model();
	bushModel->GenerateModelWithNormal(bushes, sizeof(bushes));

	for (int row = 0; row < gridRows; row++) {
		for (int col = 0; col < gridCols; col++) {
			float xPos = col * spacing;
			float yPos = 0.0f;
			float zPos = row * spacing;

			//DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), GL_TRIANGLES, "VertexShader.txt", "BlinnPhongShader.txt", camera, light, true);
			DrawableObject* treeObject = new DrawableObject(treeShader, treeModel);

			treeObject->GetTransformation()->AddComponent(new Scale(rand() % 100 / 1000.0 + 0.05f));
			treeObject->GetTransformation()->AddComponent(new Translate(xPos, yPos, zPos));

			float randomAngleY = rand() % 360;
			float randomAngleX = rand() % 40 - 20;

			treeObject->GetTransformation()->AddComponent(new Rotate(randomAngleX, randomAngleY, 0.0f));

			objects.push_back(treeObject);

			//DrawableObject* bushObject = new DrawableObject(bushes, sizeof(bushes), GL_TRIANGLES, "VertexShader.txt", "BlinnPhongShader.txt", camera, light, true);
			DrawableObject* bushObject = new DrawableObject(bushShader, bushModel);

			bushObject->GetTransformation()->AddComponent(new Scale(rand() % 100 / 500.0 + 0.05f));
			bushObject->GetTransformation()->AddComponent(new Translate(xPos - 5, yPos, zPos + spacing * 0.25f));

			objects.push_back(bushObject);
		}
	}

	Scene* scene = new Scene();

	scene->Init(objects, camera, light);

	this->AddScene(scene);
}
