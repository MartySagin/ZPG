#include "Shader.h"

Shader::Shader(GLenum mode, GLint first, GLsizei count)
{
	this->shader = 0;

	this->mode = mode;
	this->first = first;
	this->count = count;
}

void Shader::AddShaders(const char* vertex_shader, const char* fragment_shader)
{
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	
	glCompileShader(vertexShader);

	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);

	glCompileShader(fragmentShader);

	
	this->shader = glCreateProgram();
	
	glAttachShader(this->shader, vertexShader);
	glAttachShader(this->shader, fragmentShader);
	
	glLinkProgram(this->shader);
	CheckProgramLinking(this->shader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::CheckProgramLinking(GLuint program)
{

	GLint status;

	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Program linking failure: %s\n", strInfoLog);

		delete[] strInfoLog;

		exit(EXIT_FAILURE);
	}
	
}

void Shader::UseProgram()
{
	glUseProgram(this->shader);
}

void Shader::Draw()
{
	glDrawArrays(this->mode, this->first, this->count);
}
