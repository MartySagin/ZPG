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


void ShaderProgram::SetModelMatrix(glm::mat4 modelMatrix)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, "modelMatrix");

	if (idModelTransform == -1) {
		printf("Error: Cannot find uniform 'modelMatrix' in shader!\n");
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &modelMatrix[0][0]);
}

void ShaderProgram::SetViewMatrix()
{
	
	glm::mat4 viewMatrix = this->camera->GetViewMatrix();

	GLint viewLoc = glGetUniformLocation(this->shader_id, "viewMatrix");

	if (viewLoc == -1) {
		printf("Error: Cannot find uniform 'viewMatrix' in shader!\n");
	}

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
}

void ShaderProgram::SetProjectionMatrix()
{
	
	glm::mat4 projectionMatrix = this->camera->GetProjectionMatrix();
	
	GLint projectionLoc = glGetUniformLocation(this->shader_id, "projectionMatrix");

	if (projectionLoc == -1) {
		printf("Error: Cannot find uniform 'projectionMatrix' in shader!\n");
	}

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void ShaderProgram::SetNormalMatrix(glm::mat3 modelMatrix)
{
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

	GLint normalMatrixLoc = glGetUniformLocation(this->shader_id, "normalMatrix");

	if (normalMatrixLoc == -1) {
		return;
	}

	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);
}

void ShaderProgram::SetLightPosition()
{
	GLint lightPositionLoc = glGetUniformLocation(this->shader_id, "lightPosition");

	if (lightPositionLoc == -1) {
		return;
	}

	glUniform3fv(lightPositionLoc, 1, glm::value_ptr(this->light->GetPosition()));
}

void ShaderProgram::SetLightColor()
{
	GLint lightColorLoc = glGetUniformLocation(this->shader_id, "lightColor");

	if (lightColorLoc == -1) {
		return;
	}

	glUniform3fv(lightColorLoc, 1, glm::value_ptr(this->light->GetColor()));
}

void ShaderProgram::SetLightIntensity()
{
	GLint lightIntensityLoc = glGetUniformLocation(this->shader_id, "lightIntensity");

	if (lightIntensityLoc == -1) {
		return;
	}

	glUniform1f(lightIntensityLoc, this->light->GetIntensity());
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

void ShaderProgram::UpdateFromSubject()
{
	UseProgram();

	SetViewMatrix();

	SetProjectionMatrix();

	SetLightPosition();

	SetLightColor();

	SetLightIntensity();
}

