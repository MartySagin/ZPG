#include "DrawableObject.h"
#include <glm/gtc/matrix_transform.hpp>



DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, Camera* camera, Light* light, bool withNormal)
	: shaderProgram(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3, camera, light)
{

    if (withNormal)
		this->model.GenerateModelWithNormal(vertices, vertexSize);
	else
        this->model.GenerateModel(vertices, vertexSize);

    this->shaderProgram.AddShadersFromFiles(vertexShader, fragmentShader);

	this->transform = Transformation();

}

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, VertexShader* vertexShader, FragmentShader* fragmentShader, Camera* camera, Light* light, bool withNormal)
	: shaderProgram(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3, camera, light)
{

	if (withNormal)
		this->model.GenerateModelWithNormal(vertices, vertexSize);
	else
		this->model.GenerateModel(vertices, vertexSize);

	this->shaderProgram.AddShaders(vertexShader->GetShader(), fragmentShader->GetShader());

	this->transform = Transformation();

}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model) 
	: shaderProgram(*shaderProgram), model(*model)
{
	this->transform = Transformation();
}

Transformation* DrawableObject::GetTransformation()
{
	return &this->transform;
}

void DrawableObject::Draw()
{
    this->shaderProgram.UseProgram();

    this->shaderProgram.SetMat4Uniform("modelMatrix", this->transform.GetModelMatrix());

    //this->shaderProgram.SetMat3Uniform("normalMatrix", glm::transpose(glm::inverse(glm::mat3(this->transform.GetModelMatrix()))));

    this->model.BindVAO();

    this->shaderProgram.Draw();

    this->model.UnbindVAO();
}


