#include "DrawableObject.h"
#include <glm/gtc/matrix_transform.hpp>

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, bool withNormal)
    : transform(glm::mat4(1.0f)),
    shader(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3)  
{
    
    if (withNormal)
		model.GenerateModelWithNormal(vertices, vertexSize);
	else
        model.GenerateModel(vertices, vertexSize);

    shader.AddShaders(vertexShader, fragmentShader);
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
    shader.UseProgram();         
    shader.Matrix = transform;   
    model.BindVAO();             
    shader.Draw();               
    model.UnbindVAO();           
}
