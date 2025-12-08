#ifndef MATERIAL_HPP
# define MATERIAL_HPP

# include "vec3.hpp"
# include "vec4.hpp"

enum class ColorFormat { RGB, XYZ, Spectral, None };

struct ParsedColor {
	ColorFormat	format;
	vec3		rgb;
	std::string	spectralFile;
	float		spectralFactor;

	ParsedColor(void) {
		this->format = ColorFormat::None, this->spectralFactor = 1.0;
	}
};

typedef ParsedColor Ambient;
typedef ParsedColor Diffuse;
typedef ParsedColor Specular;
typedef ParsedColor TransmissionFilter;

struct Material {

	Material(void);
	Material(const Material& mat) = default;
	Material&	operator=(const Material& Material) = default;

	Ambient				ambient;			// Ka
	Diffuse				diffuse;			// Kd
	Specular			specular;			// Ks
	TransmissionFilter	transmissionFilter;	// Tf
	int					illuminationModel;	// illum
	float				opacity;			// d or Tr (= 1 - d)
	float				shininess;			// Ns
	int					sharpness;			// sharpness
	float				refractiveIndex;	// Ni

	std::string	mapAmbient;		// map_Ka
	std::string	mapDiffuse;		// map_Kd
	std::string	mapSpecular;	// map_Ks
	std::string	mapShininess;	// map_Ns
	std::string	mapOpacity;		// map_d
	std::string	mapDisp;		// disp
	std::string	mapDecal;		// decal
	std::string	mapBump;		// bump or map_bump

	std::string	mapRefl;		// refl

};

#endif // !MATERIAL_HPP
