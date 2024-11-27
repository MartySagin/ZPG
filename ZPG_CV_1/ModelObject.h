#pragma once

#include "Model.h"

struct Vertex {
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class ModelObject : public Model
{
	private:
        GLuint EBO;

        int indicesCount;

    public:
        ModelObject();

		bool GenerateModelFromOBJ(const char* fileName);

		int GetIndicesCount();
};

