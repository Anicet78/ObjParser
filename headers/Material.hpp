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

	friend std::ostream&	operator<<(std::ostream &stream, const ParsedColor& color)
	{
		if (color.format == ColorFormat::Spectral)
		{
			std::cout << "Format: Spectral" << std::endl;
			std::cout << "Spectral file: " << color.spectralFile << std::endl;
			std::cout << "Spectral factor: " << color.spectralFactor << std::endl;
			return (stream);
		}
		else if (color.format == ColorFormat::XYZ)
			std::cout << "Format: XYZ" << std::endl << "xyz: ";
		else
			std::cout << "Format: RGB" << std::endl << "rgb: ";
		std::cout << color.rgb << std::endl;
		return (stream);
	}
};

typedef ParsedColor Ambient;
typedef ParsedColor Diffuse;
typedef ParsedColor Specular;
typedef ParsedColor TransmissionFilter;

struct Dissolve {
	float	factor;
	bool	halo;
};

struct Material {

	Material(void);
	Material(const Material& mat) = default;
	Material&	operator=(const Material& Material) = default;

	Ambient				ambient;			// Ka
	Diffuse				diffuse;			// Kd
	Specular			specular;			// Ks
	TransmissionFilter	transmissionFilter;	// Tf
	int					illuminationModel;	// illum
	Dissolve			dissolve;			// d
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
	std::string	mapBump;		// bump

	std::string	mapRefl;		// refl

	static Material	BlackMaterial(void);
	static Material	WhiteMaterial(void);

	void	Print(void) const;

};

#endif // !MATERIAL_HPP
