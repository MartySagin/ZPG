#pragma once

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
class ModelClass
{
	public:
		GLuint VBO;
		GLuint VAO;

		ModelClass() {

		}

		void GenerateModel(float points[]);

};

