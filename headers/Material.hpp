#ifndef MATERIAL_HPP
# define MATERIAL_HPP

# include "vec3.hpp"
# include "vec4.hpp"

struct Material {

	Material(void);
	Material(const Material& mat);

	Material&	operator=(const Material& Material);

	vec3		ambient;
	vec3		diffuse;
	vec3		specular;
	float		shininess;
	float		opacity;
	std::string	mapKd;
	std::string	mapKs;
	std::string	bumpMap;
	int			illum;

};

#endif // !MATERIAL_HPP
