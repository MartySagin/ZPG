﻿#include "Application.h"

vector<DrawableObject> objects;
vector<DrawableObject> objects2;

void Application::Init()
{
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(1920, 1080, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(this->window, this);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Sets the key callback
	glfwSetKeyCallback(this->window, key_callback);

	glfwSetCursorPosCallback(this->window, cursor_callback);

	glfwSetMouseButtonCallback(this->window, button_callback);


	glfwSetWindowFocusCallback(this->window, window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, window_size_callback);


	//Init Camera
	this->camera = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f, 60.0f, ratio, 0.1f, 100.0f);

	
	//Init Shaders
	VertexShader* vertexShader = new VertexShader();
	FragmentShader* fragmentShaderNormal = new FragmentShader();

	FragmentShader* fragmentShaderPlain = new FragmentShader(glm::vec4(0.3f, 0.20f, 0.20f, 1.0f));

	//Scene 1
	DrawableObject plainObject(plain, sizeof(plain), GL_TRIANGLES, vertexShader->GetShader(), fragmentShaderPlain->GetShader(), this->camera, true);
	plainObject.SetScale(glm::vec3(25.0f));
	plainObject.SetPosition(glm::vec3(0.0f, 0.0f, 0.5f));

	objects.push_back(plainObject);

	srand(time(NULL));

	const int gridRows = 20;
	const int gridCols = 20;
	const float spacing = 5.0f;

	for (int row = 0; row < gridRows; row++) {
		for (int col = 0; col < gridCols; col++) {
			float xPos = col * spacing;  
			float yPos = 0.0f;  
			float zPos = row * spacing;  

			DrawableObject treeObject(tree, sizeof(tree), GL_TRIANGLES, vertexShader->GetShader(), fragmentShaderNormal->GetShader(), this->camera, true);

			treeObject.SetScale(glm::vec3(rand() % 100 / 1000.0 + 0.05f));
			treeObject.SetPosition(glm::vec3(xPos, yPos, zPos));

			float randomAngleY = rand() % 360;
			float randomAngleX = rand() % 40 - 20;

			treeObject.SetRotation(glm::vec3(randomAngleX, randomAngleY, 0.0f));

			objects.push_back(treeObject);

			DrawableObject bushObject(bushes, sizeof(bushes), GL_TRIANGLES, vertexShader->GetShader(), fragmentShaderNormal->GetShader(), this->camera, true);

			bushObject.SetScale(glm::vec3(rand() % 100 / 500.0 + 0.05f));
			bushObject.SetPosition(glm::vec3(xPos - 5, yPos, zPos + spacing * 0.25f));

			objects.push_back(bushObject);
		}
	}

	Scene scene1;
	scene1.Init(objects);

	AddScene(scene1);


	//Scene 2
	float quad[] = {
		0.5f, 0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.5f, 1.0f, 0.0f
	};

	DrawableObject sphereObject(sphere, sizeof(sphere), GL_TRIANGLES, vertexShader->GetShader(), fragmentShaderNormal->GetShader(), this->camera, true);
	sphereObject.SetScale(glm::vec3(0.5f));

	objects2.push_back(sphereObject);

	FragmentShader* fragmentShaderQuad = new FragmentShader(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	DrawableObject quadObject(quad, sizeof(quad), GL_QUADS, vertexShader->GetShader(), fragmentShaderQuad->GetShader(), this->camera, false);
	quadObject.SetScale(glm::vec3(0.5f));
	quadObject.SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));

	objects2.push_back(quadObject);

	Scene scene2;
	scene2.Init(objects2);

	AddScene(scene2);

	currentSceneIndex = 0;  
	
}

void Application::AddScene(Scene scene)
{
	scenes.push_back(scene);
}

void Application::SwitchScene()
{
	currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
}



void Application::MoveObject(int direction)
{
	printf("MoveObject %d\n", direction);
	
	for (auto& object : scenes[currentSceneIndex].objects)
	{
		if (direction == 0) {
			object.SetPosition(glm::vec3(-0.1f, 0.0f, 0.0f));
		}
		else if (direction == 1) {
			object.SetPosition(glm::vec3(0.1f, 0.0f, 0.0f));
		}
		else if (direction == 2) {
			object.SetPosition(glm::vec3(0.0f, 0.1f, 0.0f));
		}
		else if (direction == 3) {
			object.SetPosition(glm::vec3(0.0f, -0.1f, 0.0f));
		}
	}
}

void Application::RotateObject(int axis)
{
	
	for (auto& object : scenes[currentSceneIndex].objects)
	{
		if (axis == 0) {
			object.SetRotation(glm::vec3(0.0f, 0.0f, 10.0f));
		}
		else if (axis == 1) {
			object.SetRotation(glm::vec3(0.0f, 10.0f, 0.0f));
		}
	}
}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	

	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		scenes[currentSceneIndex].Render();
	

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	for (auto& model : models) {
		model.DeleteModel();
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
}



void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_LEFT) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(0); 
		}
		else if (key == GLFW_KEY_RIGHT) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(1);
		}
		else if (key == GLFW_KEY_UP) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(2);
		}
		else if (key == GLFW_KEY_DOWN) {
			((Application*)glfwGetWindowUserPointer(window))->MoveObject(3); 
		}
		else if (key == GLFW_KEY_R) {
			((Application*)glfwGetWindowUserPointer(window))->RotateObject(0); 
		}
		else if (key == GLFW_KEY_T) {
			((Application*)glfwGetWindowUserPointer(window))->RotateObject(1); 
		}
		else if (key == GLFW_KEY_SPACE) {
			((Application*)glfwGetWindowUserPointer(window))->SwitchScene(); 
		}
	}

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	static float lastFrameTime = 0.0f;
	float currentFrameTime = glfwGetTime();
	float deltaTime = currentFrameTime - lastFrameTime;

	const float maxDeltaTime = 0.01f;

	if (deltaTime > maxDeltaTime) {
		deltaTime = maxDeltaTime;
	}

	lastFrameTime = currentFrameTime;

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_W) {
			app->camera->MoveForward(deltaTime);  
		}
		else if (key == GLFW_KEY_S) {
			app->camera->MoveBackward(deltaTime);  
		}
		else if (key == GLFW_KEY_A) {
			app->camera->MoveLeft(deltaTime);  
		}
		else if (key == GLFW_KEY_D) {
			app->camera->MoveRight(deltaTime);  
		}
	}

	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		app->camera->IncreaseMovementSpeed(2.0f);
	}

	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		app->camera->DecreaseMovementSpeed(2.0f);
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{ 
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{ 
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{ 
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	static double lastX = 400, lastY = 300;
	static bool firstMouse = true;

	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	double offsetX = x - lastX;
	double offsetY = lastY - y;  

	lastX = x;
	lastY = y;

	float sensitivity = 0.1f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	app->camera->Rotate(offsetX, offsetY);
	
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Application* app = (Application*)glfwGetWindowUserPointer(window);
		app->SwitchScene();
	}

}