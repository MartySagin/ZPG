#include "Application.h"

void Application::Init()
{
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
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

	// Sets the key callback
	glfwSetKeyCallback(this->window, key_callback);

	glfwSetCursorPosCallback(this->window, cursor_callback);

	glfwSetMouseButtonCallback(this->window, button_callback);


	glfwSetWindowFocusCallback(this->window, window_focus_callback);

	glfwSetWindowIconifyCallback(this->window, window_iconify_callback);

	glfwSetWindowSizeCallback(this->window, window_size_callback);
	
}

void Application::AddScene(Scene scene)
{
	scenes.push_back(scene);
}

void Application::SwitchScene()
{
	// Cyklicky přepíná mezi scénami
	currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
}

void Application::AddShader(Shader shader)
{
	this->shaders.push_back(shader);
}

void Application::CreateModels()
{
	float points_quad[] = {
	 -0.85f, 0.85f, 0.0f,
	 -0.5f, 0.85f, 0.0f,
	 -0.5f, 0.5f, 0.0f,
	 -0.85f, 0.5f, 0.0f
	};

	float points[] = {
		 0.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};



	Model modelTree;
	modelTree.GenerateModel(tree, sizeof(tree));

	for (int i = 0; i < 20; i++) {
		this->models.push_back(modelTree);
	}

	Model modelBush;
	modelBush.GenerateModel(bushes, sizeof(bushes));

	for (int i = 0; i < 20; i++) {
		this->models.push_back(modelBush);
	}

	

}

void Application::CreateShaders()
{
	const char* vertex_shader =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"  
		"layout(location = 1) in vec3 aColor;\n"  
		"out vec3 ourColor;\n"
		"uniform mat4 modelMatrix;\n"
		"void main() {\n"
		"    gl_Position = modelMatrix * vec4(aPos, 1.0);\n"  
		"    ourColor = aColor;\n"
		"}\n";



	const char* fragment_shader =
		"#version 330 core\n"
		"in vec3 ourColor;\n" 
		"out vec4 fragColor;\n"
		"void main() {\n"
		"    fragColor = vec4(ourColor, 1.0);\n"  
		"}\n";

	const char* fragment_shader_quad =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0, 1, 0, 1.0);"
		"}";




	srand(time(NULL));

	for (int i = 0; i < 20; i++) {
		glm::mat4 Matrix = glm::mat4(1.0f);

	

		Matrix = glm::scale(glm::mat4(1.0f), glm::vec3(rand()%100/1000.0+0.05f));


		float randomAngleY = rand() % 45;  
		Matrix = glm::rotate(Matrix, glm::radians(randomAngleY), glm::vec3(0.0f, 1.0f, 0.0f));

		float randomAngleX = rand() % 45;  
		Matrix = glm::rotate(Matrix, glm::radians(randomAngleX), glm::vec3(1.0f, 0.0f, 0.0f));


		Matrix = glm::translate(Matrix, glm::vec3(rand()%20-8, rand()%10-5, 0.0f));


		Shader shaderTree(GL_TRIANGLES, 0, 92814, Matrix);
		shaderTree.AddShaders(vertex_shader, fragment_shader);

		this->shaders.push_back(shaderTree);
	}

	for (int i = 0; i < 20; i++) {
		glm::mat4 Matrix = glm::mat4(1.0f);

		float randomAngle = rand() % 360;  
		Matrix = glm::rotate(Matrix, glm::radians(randomAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		Matrix = glm::scale(glm::mat4(1.0f), glm::vec3(rand() % 100 / 500.0 + 0.05f));
		Matrix = glm::translate(Matrix, glm::vec3(rand() % 8 - 5, rand() % 8 - 5, 0.0f));

		Shader shaderBush(GL_TRIANGLES, 0, 8730, Matrix);
		shaderBush.AddShaders(vertex_shader, fragment_shader);

		this->shaders.push_back(shaderBush);
	}
		

	

}

void Application::MoveObject(int direction)
{
	
	for (auto& shader : shaders)
	{
		if (direction == 0) {
			shader.Matrix = glm::translate(shader.Matrix, glm::vec3(-0.1f, 0.0f, 0.0f));
		}
		else if (direction == 1) {
			shader.Matrix = glm::translate(shader.Matrix, glm::vec3(0.1f, 0.0f, 0.0f)); 
		}
		else if (direction == 2) {
			shader.Matrix = glm::translate(shader.Matrix, glm::vec3(0.0f, 0.1f, 0.0f)); 
		}
		else if (direction == 3) {
			shader.Matrix = glm::translate(shader.Matrix, glm::vec3(0.0f, -0.1f, 0.0f));
		}
	}
}

void Application::RotateObject(int axis)
{
	
	for (auto& shader : shaders)
	{
		if (axis == 0) {
			shader.Matrix = glm::rotate(shader.Matrix, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
		}
		else if (axis == 1) {
			shader.Matrix = glm::rotate(shader.Matrix, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
		}
	}
}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	

	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < this->models.size(); i++) {
			this->shaders[i].UseProgram();
			this->models[i].BindVAO();
			this->shaders[i].Draw();
			this->models[i].UnbindVAO();
		}
	

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
	printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		// Přepne na další scénu po stisknutí pravého tlačítka myši
		Application* app = (Application*)glfwGetWindowUserPointer(window);
		app->SwitchScene();
	}

}