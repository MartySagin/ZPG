#include "Model.h"

Model::Model()
{
	this->VAO = 0;
	this->VBO = 0;
}

void Model::GenerateModel(float* points, GLsizeiptr size)
{
    
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::BindVAO()
{
    glBindVertexArray(this->VAO);
}

void Model::UnbindVAO()
{
    glBindVertexArray(0);
}

void Model::DeleteModel()
{
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);
}