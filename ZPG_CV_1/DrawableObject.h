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

        bool hasNormal;

    public:

        DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, VertexShader* vertexShader, FragmentShader* fragmentShader, Camera* camera, Light* light, bool withNormal);

        DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, const char* vertexShader, const char* fragmentShader, Camera* camera, Light* light, bool withNormal);

	    DrawableObject(ShaderProgram* shaderProgram, Model* model);

	    Transformation* GetTransformation();

        void Draw();
};
