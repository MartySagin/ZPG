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
#include "Light.h"
#include "ShaderLoader.h"

class Camera;

class ShaderProgram : Observer
{
	private:
		GLuint shader_id;

		GLenum mode;
		GLint first;
		GLsizei count;

		Camera* camera;

		Light* light;

		ShaderLoader* shaderLoader;

	public:
		ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera* camera, Light* light);
		
		void AddShaders(const char* vertex_shader, const char* fragment_shader);

		void AddShadersFromFiles(const char* vertex_shader, const char* fragment_shader);

		void SetMat4Uniform(const char* uniformName, glm::mat4 matrix);

		void SetMat3Uniform(const char* uniformName, glm::mat3 matrix);

		void SetVec3Uniform(const char* uniformName, glm::vec3 vector);

		void SetFloatUniform(const char* uniformName, float value);

		void CheckProgramLinking(GLuint program);

		void CheckProgramCompiling(GLuint program);

		void UseProgram();

		void Draw();

		void UpdateFromSubject() override;
};

