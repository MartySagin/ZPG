#include "Material.h"

Material::Material(float ambient, float diffuse, float specular, int shininess)
{
	this->ra = ambient;
	this->rd = diffuse;
	this->rs = specular;
	this->shininess = shininess;
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

void Material::SetShininess(int shininess)
{
	this->shininess = shininess;
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

int Material::GetShininess()
{
	return this->shininess;
}
