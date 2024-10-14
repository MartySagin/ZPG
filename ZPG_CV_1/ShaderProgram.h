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

#include <stdio.h>
#include "Shader.h"

class ShaderProgram
{
	private:
		GLuint shader_id;

		GLenum mode;
		GLint first;
		GLsizei count;


	public:
		glm::mat4 Matrix;

		ShaderProgram(GLenum mode, GLint first, GLsizei count);
		ShaderProgram(GLenum mode, GLint first, GLsizei count, glm::mat4 Matrix);
		
		void AddShaders(Shader vertex_shader, Shader fragment_shader);

		void SetMatrix(glm::mat4 Matrix);

		void CheckProgramLinking(GLuint program);

		void UseProgram();

		void Draw();
};

