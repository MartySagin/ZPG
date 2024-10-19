#pragma once

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>
#include "ShaderProgram.h"
#include "Model.h"
#include "bushes.h"
#include "sphere.h"
#include "tree.h"
#include <random>
#include "Scene.h"
#include "Camera.h"
#include "plain.h"
#include "FragmentShader.h"
#include "VertexShader.h"

using namespace std;

class Application
{
	public:
		GLFWwindow* window;

		vector<ShaderProgram> shaders;
		vector<Model> models;

		vector<Scene> scenes;    
		int currentSceneIndex;

	public:
		void Init();

		void AddScene(Scene scene);

		void SwitchScene();

		void MoveObject(int direction);

		void RotateObject(int axis);

		void Run();

		static void error_callback(int error, const char* description);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void window_focus_callback(GLFWwindow* window, int focused);

		static void window_iconify_callback(GLFWwindow* window, int iconified);

		static void window_size_callback(GLFWwindow* window, int width, int height);

		static void cursor_callback(GLFWwindow* window, double x, double y);

		static void button_callback(GLFWwindow* window, int button, int action, int mode);

};

