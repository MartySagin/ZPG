#include "DrawableObject.h"
#include <glm/gtc/matrix_transform.hpp>

DrawableObject::DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, Camera* camera, bool withNormal)
    : transformation(),
    shaderProgram(drawMode, 0, withNormal == true ? vertexSize / sizeof(float) / 6 : vertexSize / sizeof(float) / 3, camera)  
{
    
    if (withNormal)
		model.GenerateModelWithNormal(vertices, vertexSize);
	else
        model.GenerateModel(vertices, vertexSize);

    shaderProgram.AddShaders(vertexShader, fragmentShader);
}


void DrawableObject::SetPosition(glm::vec3 position)
{
    transformation.SetPosition(position);
}


void DrawableObject::SetRotation(glm::vec3 rotationDegrees)
{
    transformation.SetRotation(rotationDegrees);
}


void DrawableObject::SetScale(glm::vec3 scale)
{
    transformation.SetScale(scale);
}


void DrawableObject::Draw()
{
    shaderProgram.UseProgram();         

    shaderProgram.SetMatrix(transformation.GetMatrix());

    model.BindVAO();             

    shaderProgram.Draw();

    model.UnbindVAO();           
}
