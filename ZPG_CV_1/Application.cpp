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


	/*Model modelTriangle;
	modelTriangle.GenerateModel(points, sizeof(points));  

	this->models.push_back(modelTriangle);

	Model modelQuads;
	modelQuads.GenerateModel(points_quad, sizeof(points_quad));

	this->models.push_back(modelQuads);*/


	/*Model modelBush;
	modelBush.GenerateModel(bushes, sizeof(bushes));

	this->models.push_back(modelBush);*/

	Model modelTree;
	modelTree.GenerateModel(tree, sizeof(tree));

	this->models.push_back(modelTree);

	Model modelTree2;
	modelTree2.GenerateModel(tree, sizeof(tree));

	this->models.push_back(modelTree2);

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


	/*Shader shaderTriangle(GL_TRIANGLES, 0, 3);
	shaderTriangle.AddShaders(vertex_shader, fragment_shader);
	
	this->shaders.push_back(shaderTriangle);

	Shader shaderQuads(GL_QUADS, 0, 4);
	shaderQuads.AddShaders(vertex_shader, fragment_shader_quad);

	this->shaders.push_back(shaderQuads);*/

	/*Shader shaderBush(GL_TRIANGLES, 0, 8730);
	shaderBush.AddShaders(vertex_shader, fragment_shader);

	this->shaders.push_back(shaderBush);*/

	Shader shaderTree(GL_TRIANGLES, 0, 92814);
	shaderTree.AddShaders(vertex_shader, fragment_shader);

	this->shaders.push_back(shaderTree);

	Shader shaderTree2(GL_TRIANGLES, 0, 92814);
	shaderTree2.AddShaders(vertex_shader, fragment_shader);

	this->shaders.push_back(shaderTree);

}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 C = glm::mat4(1.0f);

	vector<glm::mat4> v;


	C = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)); 
	C = glm::translate(C, glm::vec3(-5.0f, 0.0f, 0.0f)); 

	M = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));

	v.push_back(M);
	v.push_back(C);

	while (!glfwWindowShouldClose(this->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*for (size_t i = 0; i < models.size(); ++i)
		{
			shaders[i].UseProgram(v[i]);
			models[i].BindVAO();
			shaders[i].Draw();
			models[i].UnbindVAO();
		}*/

		shaders[0].UseProgram(v[0]);
		models[0].BindVAO();
		shaders[0].Draw();
		models[0].UnbindVAO();

		shaders[1].UseProgram(v[1]);
		models[1].BindVAO();
		shaders[1].Draw();
		models[1].UnbindVAO();

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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
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

	if (action == GLFW_PRESS) {
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}

}