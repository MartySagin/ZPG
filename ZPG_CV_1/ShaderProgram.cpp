#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count)
{
	this->shaderLoader = nullptr;
	
	this->shader_id = 0;

	this->mode = mode;
	this->first = first;
	this->count = count;

}

ShaderProgram::ShaderProgram(GLenum mode, GLsizei count)
{
	this->shaderLoader = nullptr;

	this->shader_id = 0;

	this->mode = mode;
	this->first = 0;
	this->count = count;

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

void ShaderProgram::SetIntUniform(const char* uniformName, int value)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_id, uniformName);

	if (idModelTransform == -1) {
		return;
	}

	glUniform1i(idModelTransform, value);
}

void ShaderProgram::SetNumberOfLights(int numberOfLights)
{
	this->UseProgram();

	this->SetIntUniform("numberOfLights", numberOfLights);

	this->DisableProgram();
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

void ShaderProgram::DisableProgram()
{
	glUseProgram(0);
}

void ShaderProgram::Draw()
{
	
	glDrawArrays(this->mode, this->first, this->count);
		
}

void ShaderProgram::DrawOBJ() 
{

	glDrawElements(this->mode, this->count, GL_UNSIGNED_INT, NULL);

}

void ShaderProgram::UpdateFromSubject(Subject* subject)
{
	UseProgram();

	if (typeid(*subject) == typeid(Camera)) {

		Camera* camera = (Camera*)subject;
		
		SetMat4Uniform("viewMatrix", camera->GetViewMatrix());

		SetMat4Uniform("projectionMatrix", camera->GetProjectionMatrix());

		SetVec3Uniform("viewPosition", camera->GetPosition());

	}
	else if (typeid(*subject) == typeid(Light)) {

		Light* light = (Light*)subject;

		int index = light->GetIndex();

		string prefix = "lights[" + to_string(index) + "].";

		SetVec3Uniform((prefix + "position").c_str(), light->GetPosition());

		SetVec3Uniform((prefix + "color").c_str(), light->GetColor());

		SetFloatUniform((prefix + "intensity").c_str(), light->GetIntensity());

		SetFloatUniform((prefix + "ambientStrength").c_str(), light->GetAmbientStrength());

		SetIntUniform((prefix + "type").c_str(), light->GetType());

		SetVec3Uniform((prefix + "direction").c_str(), light->GetDirection());

		SetFloatUniform((prefix + "cutOff").c_str(), glm::cos(glm::radians(light->GetCutOff())));

		SetFloatUniform((prefix + "outerCutOff").c_str(), glm::cos(glm::radians(light->GetOuterCutOff())));

	}

	DisableProgram();

}

