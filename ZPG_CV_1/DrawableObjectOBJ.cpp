#include "DrawableObjectOBJ.h"

DrawableObjectOBJ::DrawableObjectOBJ(ShaderProgram* shaderProgram, ModelObject* model, Material* material, Texture* texture) : DrawableObject(shaderProgram, model, material, texture)
{
}

void DrawableObjectOBJ::Draw()
{
	this->shaderProgram.UseProgram();

	if (this->texture != nullptr) {
		this->texture->Bind();

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

	this->model.BindVAO();

	this->shaderProgram.DrawOBJ();

	this->model.UnbindVAO();

	if (this->texture) {
		this->texture->Unbind();
	}

	this->shaderProgram.DisableProgram();
}
