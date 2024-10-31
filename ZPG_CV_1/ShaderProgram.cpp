#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera* camera, Light* light)
{
	this->shader_id = 0;

	this->mode = mode;
	this->first = first;
	this->count = count;

	this->camera = camera;

	camera->AddObserver(this);

	this->light = light;

	light->AddObserver(this);

}

void ShaderProgram::AddShaders(const char* vertex_shader, const char* fragment_shader)
{
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	CheckProgramCompiling(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);

	CheckProgramCompiling(fragmentShader);

	this->shader_id = glCreateProgram();

	glAttachShader(this->shader_id, vertexShader);
	glAttachShader(this->shader_id, fragmentShader);
	glLinkProgram(this->shader_id);

	CheckProgramLinking(this->shader_id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::AddShadersFromFiles(const char* vertex_shader, const char* fragment_shader)
{
	this->shaderLoader = new ShaderLoader(vertex_shader, fragment_shader, &this->shader_id);
}

void ShaderProgram::SetMat4Uniform(const char* uniformName, glm::mat4 matrix)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::SetMat3Uniform(const char* uniformName, glm::mat3 matrix)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniformMatrix3fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::SetVec3Uniform(const char* uniformName, glm::vec3 vector)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniform3fv(idModelTransform, 1, glm::value_ptr(vector));
}

void ShaderProgram::SetFloatUniform(const char* uniformName, float value)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniform1f(idModelTransform, value);
}

void ShaderProgram::CheckProgramLinking(GLuint program)
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

void ShaderProgram::CheckProgramCompiling(GLuint program) {
	GLint status;

	glGetProgramiv(program, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Program compiling failure: %s\n", strInfoLog);

		delete[] strInfoLog;

		exit(EXIT_FAILURE);
	}
}

void ShaderProgram::UseProgram()
{
	glUseProgram(this->shader_id);
}

void ShaderProgram::Draw()
{
	glDrawArrays(this->mode, this->first, this->count);
}

void ShaderProgram::UpdateFromSubject(Subject* subject)
{
	UseProgram();

	if (typeid(*subject) == typeid(Camera)) {
		
		SetMat4Uniform("viewMatrix", camera->GetViewMatrix());

		SetMat4Uniform("projectionMatrix", camera->GetProjectionMatrix());

		SetVec3Uniform("viewPosition", camera->GetPosition());
	}
	else if (typeid(*subject) == typeid(Light)) {
		
		SetVec3Uniform("lightPosition", light->GetPosition());

		SetVec3Uniform("lightColor", light->GetColor());

		SetFloatUniform("lightIntensity", light->GetIntensity());

		SetVec3Uniform("objectColor", light->GetObjectColor());

		SetFloatUniform("ambientStrength", light->GetAmbientStrength());
	}

}

