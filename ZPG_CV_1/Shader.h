#pragma once

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

class Shader
{
	private:
		GLuint shader;
		GLuint fragmentShader;
		GLuint vertexShader;

	public:
		Shader() {
			this->shader = glCreateProgram();
			this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
			this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		}
		
		void AddShader(const char* shader, bool isVertexShader);
		void UseProgram();
		void Draw(GLenum mode, GLint first, GLsizei count);
		void AttachShadersAndLinkProgram();
};

