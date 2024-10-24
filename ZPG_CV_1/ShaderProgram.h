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

		void SetModelMatrix(glm::mat4 modelMatrix);

		void SetViewMatrix();     
		
		void SetProjectionMatrix();

		void SetNormalMatrix(glm::mat3 modelMatrix);

		void SetLightPosition();

		void SetLightColor();

		void SetLightIntensity();

		void SetViewPosition();

		void SetObjectColor();

		void SetAmbientStrength();

		void CheckProgramLinking(GLuint program);

		void CheckProgramCompiling(GLuint program);

		void UseProgram();

		void Draw();

		void UpdateFromSubject() override;
};

