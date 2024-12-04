#pragma once

#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Texture.h"
#include "ModelObject.h"

class DrawableObject
{
    protected:

        Model model;

		Material material;

        ShaderProgram shaderProgram;

        Transformation transform;

        Texture* texture;

        glm::vec3 objectColor;

        int objectID;

    public:

	    DrawableObject(ShaderProgram* shaderProgram, Model* model, glm::vec3 objectColor, Material* material);

        DrawableObject(ShaderProgram* shaderProgram, Model* model, Material* material, Texture* texture);

		DrawableObject(ShaderProgram* shaderProgram, ModelObject* model, Material* material, Texture* texture);

		void SetObjectID(int objectID);

        int GetObjectID();

	    Transformation* GetTransformation();

		ShaderProgram* GetShaderProgram();

        virtual void Draw();
};
