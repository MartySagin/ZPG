#pragma once

#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"

class DrawableObject
{
    private:
        Model model;

        ShaderProgram shaderProgram;

        Transformation transform;

        glm::vec3 objectColor;

    public:

        DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, glm::vec3 objectColor, VertexShader* vertexShader, FragmentShader* fragmentShader, Camera* camera, vector<Light*> lights, bool withNormal);

        DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, glm::vec3 objectColor, const char* vertexShader, const char* fragmentShader, Camera* camera, vector<Light*> lights, bool withNormal);

	    DrawableObject(ShaderProgram* shaderProgram, Model* model, glm::vec3 objectColor);

	    Transformation* GetTransformation();

        void Draw();
};
