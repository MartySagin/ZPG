#pragma once

#include "DrawableObject.h"

class DrawableObjectOBJ : public DrawableObject
{
	public:
		DrawableObjectOBJ(ShaderProgram* shaderProgram, ModelObject* model, Material* material, Texture* texture);

		void virtual Draw() override;

};


