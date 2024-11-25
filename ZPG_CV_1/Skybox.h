#pragma once

#include "DrawableObject.h"

class Skybox : public DrawableObject
{
	private:
		bool followCamera;

	public:
		Skybox(ShaderProgram* shaderProgram, Model* model, Material* material, Texture* texture);

		void SetFollowCamera(bool followCamera);

		bool GetFollowCamera();

		virtual void Draw() override;
};

