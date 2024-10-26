#include "Application.h"

void Application::Init()
{
	
	glfwSetErrorCallback(Controller::ErrorCallback);

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

	glfwSetErrorCallback(Controller::ErrorCallback);

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

	// Hide cursor
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Inicializace Controlleru
	this->controller = new Controller();

	// Set Callbacks
	glfwSetKeyCallback(this->window, Controller::KeyCallback);

	glfwSetCursorPosCallback(this->window, Controller::CursorCallback);

	glfwSetMouseButtonCallback(this->window, Controller::ButtonCallback);

	glfwSetWindowFocusCallback(this->window, Controller::WindowFocusCallback);

	glfwSetWindowIconifyCallback(this->window, Controller::WindowIconifyCallback);

	glfwSetWindowSizeCallback(this->window, Controller::WindowSizeCallback);


	//Init Scene Maker
	this->sceneMaker = new SceneMaker(ratio);

	//Init Scene 1
	this->sceneMaker->CreateSceneTriangle();

	//Init Scene 2	
	this->sceneMaker->CreateSceneForest();

	//Init Scene 3
	this->sceneMaker->CreateSceneFourSpheresLight();

	//Init Scene 4
	this->sceneMaker->CreateSceneWithMoreModels();

	
}


SceneMaker* Application::GetSceneMaker()
{
	return this->sceneMaker;
}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	

	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->sceneMaker->GetCurrentScene()->Render();

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
}
