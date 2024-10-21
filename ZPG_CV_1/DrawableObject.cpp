#include "DrawableObject.h"
#include <glm/gtc/matrix_transform.hpp>

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, Camera* camera, bool withNormal)
    : shaderProgram(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3, camera)  
{

    if (withNormal)
		this->model.GenerateModelWithNormal(vertices, vertexSize);
	else
        this->model.GenerateModel(vertices, vertexSize);

    this->shaderProgram.AddShaders(vertexShader, fragmentShader);

}


void DrawableObject::SetPosition(glm::vec3 position)
{
    transform = glm::translate(transform, position);
}

void DrawableObject::SetRotation(glm::vec3 rotationDegrees)
{
    transform = glm::rotate(transform, glm::radians(rotationDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotationDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotationDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void DrawableObject::SetScale(glm::vec3 scale)
{
    transform = glm::scale(transform, scale);
}


void DrawableObject::Draw()
{
    this->shaderProgram.UseProgram();         

    this->shaderProgram.SetModelMatrix(this->transform);

    this->shaderProgram.SetNormalMatrix(this->transform);

    this->model.BindVAO();             

    this->shaderProgram.Draw();

    this->model.UnbindVAO();           
}


