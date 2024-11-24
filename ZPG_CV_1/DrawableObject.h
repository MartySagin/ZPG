#pragma once

#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Material.h"
#include "Texture.h"

class DrawableObject
{
    private:

        Model model;

		Material material;

        ShaderProgram shaderProgram;

        Transformation transform;

        Texture* texture;

        glm::vec3 objectColor;

    public:

        DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, glm::vec3 objectColor, Material* material, VertexShader* vertexShader, FragmentShader* fragmentShader, bool withNormal);

        DrawableObject(const float* vertices, GLsizeiptr vertexSize, GLenum drawMode, glm::vec3 objectColor, Material* material, const char* vertexShader, const char* fragmentShader, bool withNormal);

	    DrawableObject(ShaderProgram* shaderProgram, Model* model, glm::vec3 objectColor, Material* material);

        DrawableObject(ShaderProgram* shaderProgram, Model* model, glm::vec3 objectColor, Material* material, Texture* texture);

        void SetTexture(Texture* texture);

	    Transformation* GetTransformation();

		ShaderProgram* GetShaderProgram();

        void Draw();
};
