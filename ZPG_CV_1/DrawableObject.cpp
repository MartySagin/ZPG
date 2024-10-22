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



void DrawableObject::Draw()
{
    this->shaderProgram.UseProgram();         

    this->shaderProgram.SetModelMatrix(this->transform.GetMatrix());

    this->shaderProgram.SetNormalMatrix(this->transform.GetMatrix());

    this->model.BindVAO();             

    this->shaderProgram.Draw();

    this->model.UnbindVAO();           
}


