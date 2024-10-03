#include "Shader.h"

void Shader::AddShader(const char* shader, bool isVertexShader)
{
	
	if (isVertexShader) {
		glShaderSource(vertexShader, 1, &shader, NULL);
		glCompileShader(vertexShader);
	}
	else {
		glShaderSource(fragmentShader, 1, &shader, NULL);
		glCompileShader(fragmentShader);
	}

}

void Shader::AttachShadersAndLinkProgram() {
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);

	glLinkProgram(shader);
}

void Shader::UseProgram()
{
	glUseProgram(shader);
}

void Shader::Draw(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays(mode, first, count);
}
