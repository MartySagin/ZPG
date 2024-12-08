#include "Skybox.h"

Skybox::Skybox(ShaderProgram* shaderProgram, Model* model, Material* material, Texture* texture) : DrawableObject(shaderProgram, model, material, texture)
{
	this->followCamera = true;
}

void Skybox::SetFollowCamera(bool followCamera)
{
	this->followCamera = followCamera;
}

bool Skybox::GetFollowCamera()
{
	return this->followCamera;
}

void Skybox::Draw()
{
	
	if (this->followCamera) {
		glDisable(GL_DEPTH_TEST);
	}

	this->shaderProgram.UseProgram();

	this->shaderProgram.SetIntUniform("followCamera", this->followCamera);

	if (texture != nullptr) {
		texture->ActivateTexture();

		this->shaderProgram.SetIntUniform("hasTexture", 1);

		this->shaderProgram.SetIntUniform("textureUnit", texture->GetTextureUnit());
	}
	else {
		this->shaderProgram.SetIntUniform("hasTexture", 0);

		this->shaderProgram.SetVec3Uniform("objectColor", this->objectColor);
	}

	this->shaderProgram.SetMat4Uniform("modelMatrix", this->transform.GetModelMatrix());

	this->shaderProgram.SetFloatUniform("material.ra", this->material.GetAmbientCoefficient());

	this->shaderProgram.SetFloatUniform("material.rd", this->material.GetDiffuseCoefficient());

	this->shaderProgram.SetFloatUniform("material.rs", this->material.GetSpecularCoefficient());

	this->shaderProgram.SetFloatUniform("material.shininess", this->material.GetShininess());

	this->model.BindVAO();

	this->shaderProgram.Draw();

	this->model.UnbindVAO();

	this->shaderProgram.DisableProgram();

	glEnable(GL_DEPTH_TEST);
}

void Skybox::UpdateFromSubject(Subject* subject)
{
	Camera* camera = (Camera*)(subject);
	
	if (this->followCamera) {
		
		if (camera != nullptr) {
			this->transform.ClearComponents();

			this->transform.AddComponent(new Translate(camera->GetPosition()));
		}
	}
	
}



