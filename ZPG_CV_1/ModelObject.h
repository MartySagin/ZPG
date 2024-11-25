#pragma once

#include "Model.h"

class ModelObject : public Model
{
	private:
        GLuint EBO;

        int indicesCount;

        struct Vertex {
            float Position[3];
            float Normal[3];
            float Texture[2];
            float Tangent[3];
        };

    public:
        ModelObject();

		bool GenerateModelFromOBJ(const char* fileName);

		int GetIndicesCount();
};

