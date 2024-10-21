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
#include "Camera.h"
#include "Observer.h"

class Camera;

class ShaderProgram : Observer
{
	private:
		GLuint shader_id;

		GLenum mode;
		GLint first;
		GLsizei count;

		Camera* camera;

	public:
		glm::mat4 Matrix;

		ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera* camera);
		
		void AddShaders(const char* vertex_shader, const char* fragment_shader);

		void SetMatrix(glm::mat4 Matrix);

		void SetViewMatrix();     
		
		void SetProjectionMatrix();

		void CheckProgramLinking(GLuint program);

		void CheckProgramCompiling(GLuint program);

		void UseProgram();

		void Draw();

		void Update() override;
};

