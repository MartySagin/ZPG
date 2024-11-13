#include "Material.h"

Material::Material(float ambient, float diffuse, float specular)
{
	this->ra = ambient;
	this->rd = diffuse;
	this->rs = specular;
}

void Material::SetAmbientCoefficient(float ambient)
{
	this->ra = ambient;
}

void Material::SetDiffuseCoefficient(float diffuse)
{
	this->rd = diffuse;
}

void Material::SetSpecularCoefficient(float specular)
{
	this->rs = specular;
}

float Material::GetAmbientCoefficient()
{
	return this->ra;
}

float Material::GetDiffuseCoefficient()
{
	return this->rd;
}

float Material::GetSpecularCoefficient()
{
	return this->rs;
}
