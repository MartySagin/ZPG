#include "DrawableObject.h"
#include <glm/gtc/matrix_transform.hpp>



DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, glm::vec3 objectColor, Material* material, const char* vertexShader, const char* fragmentShader, Camera* camera, vector<Light*> lights, bool withNormal)
	: shaderProgram(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3, camera, lights), material(*material)
{

    if (withNormal)
		this->model.GenerateModelWithNormal(vertices, vertexSize);
	else
        this->model.GenerateModel(vertices, vertexSize);

    this->shaderProgram.AddShadersFromFiles(vertexShader, fragmentShader);

	this->transform = Transformation();

	this->objectColor = objectColor;

}

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, glm::vec3 objectColor, Material* material, VertexShader* vertexShader, FragmentShader* fragmentShader, Camera* camera, vector<Light*> lights, bool withNormal)
	: shaderProgram(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3, camera, lights), material(*material)
{

	if (withNormal)
		this->model.GenerateModelWithNormal(vertices, vertexSize);
	else
		this->model.GenerateModel(vertices, vertexSize);

	this->shaderProgram.AddShaders(vertexShader->GetShader(), fragmentShader->GetShader());

	this->transform = Transformation();

	this->objectColor = objectColor;

}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model, glm::vec3 objectColor, Material* material)
	: shaderProgram(*shaderProgram), model(*model), material(*material)
{
	this->transform = Transformation();

	this->objectColor = objectColor;
}

Transformation* DrawableObject::GetTransformation()
{
	return &this->transform;
}

void DrawableObject::Draw()
{
    this->shaderProgram.UseProgram();

    this->shaderProgram.SetMat4Uniform("modelMatrix", this->transform.GetModelMatrix());

	this->shaderProgram.SetVec3Uniform("objectColor", this->objectColor);

    //this->shaderProgram.SetMat3Uniform("normalMatrix", glm::transpose(glm::inverse(glm::mat3(this->transform.GetModelMatrix()))));

	this->shaderProgram.SetFloatUniform("material.ra", this->material.GetAmbientCoefficient());

	this->shaderProgram.SetFloatUniform("material.rd", this->material.GetDiffuseCoefficient());

	this->shaderProgram.SetFloatUniform("material.rs", this->material.GetSpecularCoefficient());

    this->model.BindVAO();

    this->shaderProgram.Draw();

    this->model.UnbindVAO();

	this->shaderProgram.DisableProgram();
}


