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
#include <random>
#include "Scene.h"
#include "Camera.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"
#include "Light.h"
#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"
#include "SceneMaker.h"
#include "Controller.h"

using namespace std;

class Application
{
	private:
		GLFWwindow* window;

		SceneMaker* sceneMaker;

		Controller* controller;

	public:
		void Init();

		SceneMaker* GetSceneMaker();

		void Run();

};

