#include "Material.hpp"

Material::Material()
{
	this->shininess = 0;
	this->opacity = 1.0;
	this->illum = 2;
}

Material::Material(const Material& Material)
{
	if (this != &Material)
		*this = Material;
	return ;
}

Material&	Material::operator=(const Material& Material)
{
	(void)Material;
	// if (this != &Material)
	return (*this);
}
