#include "MtlParser.hpp"

Material::Material(void)
{
	this->illuminationModel = 2;
	this->dissolve.factor = 1.0f;
	this->dissolve.halo = false;
	this->shininess = 0;
	this->sharpness = 60;
	this->refractiveIndex = 1.0f;
}

Material	Material::BlackMaterial(void)
{
	Material mat;
	mat.ambient.format = ColorFormat::RGB;
	mat.ambient.rgb = vec3(0, 0, 0);
	mat.diffuse.format = ColorFormat::RGB;
	mat.diffuse.rgb = vec3(0, 0, 0);
	mat.specular.format = ColorFormat::RGB;
	mat.specular.rgb = vec3(0, 0, 0);
	mat.transmissionFilter.format = ColorFormat::RGB;
	mat.transmissionFilter.rgb = vec3(0, 0, 0);
	return (mat);
}

Material	Material::WhiteMaterial(void)
{
	Material mat;
	mat.ambient.format = ColorFormat::RGB;
	mat.ambient.rgb = vec3(1, 1, 1);
	mat.diffuse.format = ColorFormat::RGB;
	mat.diffuse.rgb = vec3(1, 1, 1);
	mat.specular.format = ColorFormat::RGB;
	mat.specular.rgb = vec3(1, 1, 1);
	mat.transmissionFilter.format = ColorFormat::RGB;
	mat.transmissionFilter.rgb = vec3(1, 1, 1);
	return (mat);
}

void	Material::Print(void) const
{
	std::cout << "Ambient: " << std::endl << this->ambient << std::endl;
	std::cout << "Diffuse: " << std::endl << this->diffuse << std::endl;
	std::cout << "Specular: " << std::endl << this->specular << std::endl;
	std::cout << "TransmissionFilter: " << std::endl << this->transmissionFilter << std::endl;
	std::cout << "Illumination model: " << this->illuminationModel << std::endl;
	std::cout << "Dissolve factor: " << this->dissolve.factor << std::endl;
	std::cout << "Dissolve halo: " << this->dissolve.halo << std::endl;
	std::cout << "Shininess: " << this->shininess << std::endl;
	std::cout << "Sharpness: " << this->sharpness << std::endl;
	std::cout << "Refractive index: " << this->refractiveIndex << std::endl;
}

void	MtlParser::NewMaterial(std::istringstream& ss)
{
	std::string materialName = "";
	if (!(ss >> materialName) || materialName == "")
		ThrowError("A name for the material must be provided in `newmtl`", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Materials can only have one name and it cannot contains blanks in `newmtl`", ss, this->countLines, this->fileName);

	this->materials[materialName];
	this->currentMaterial = materialName;
}

void	MtlParser::ParseColor(std::istringstream& ss, std::string statement, ParsedColor& color)
{
	std::string token;
	if (!(ss >> token))
		ThrowError("Not enough arguments in `" + statement + "`", this->countLines, this->fileName);

	if (token == "spectral")
	{
		color.format = ColorFormat::Spectral;
		if (!(ss >> token))
			ThrowError("Not enough arguments in `" + statement + " spectral` (file.rfl, [factor])", this->countLines, this->fileName);
		color.spectralFile = token;
		if (ss >> token)
			color.spectralFactor = StrToFloat(token, statement + " spectral", this->countLines, this->fileName);
	}
	else
	{
		float r, g, b;

		if (token == "xyz")
		{
			if (!(ss >> token))
				ThrowError("Not enough arguments in `" + statement + " xyz` (x, [y, z])", this->countLines, this->fileName);
			color.format = ColorFormat::XYZ;
		}
		else
			color.format = ColorFormat::RGB;

		r = StrToFloat(token, statement, this->countLines, this->fileName);

		ss >> token;
		if (!ss.eof())
			g = StrToFloat(token, statement, this->countLines, this->fileName);
		else
			g = r;

		if (!ss.eof() && ss >> token && !ss.eof())
			b = StrToFloat(token, statement, this->countLines, this->fileName);
		else
			b = r;

		color.rgb = vec3(r, g, b);
	}

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `" + statement + "`", ss, this->countLines, this->fileName);
}

void	MtlParser::SetIllumModel(std::istringstream& ss)
{
	int& illum = this->materials[this->currentMaterial].illuminationModel;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `illum` (number missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `illum`", ss, this->countLines, this->fileName);

	illum = StrToInt(value, "illum", this->countLines, this->fileName);
	if (illum < 0 || illum > 10)
		ThrowError("Invalid value in `illum`, the number should be between 0 and 10", value, this->countLines, this->fileName);
}

void	MtlParser::SetDissolve(std::istringstream& ss, bool needInversion)
{
	Dissolve& dissolve = this->materials[this->currentMaterial].dissolve;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `d` ([-halo] factor)", this->countLines, this->fileName);

	if (value == "-halo")
	{
		dissolve.halo = true;
		if (!(ss >> value))
			ThrowError("Not enough arguments in `d` ([-halo] factor)", this->countLines, this->fileName);
	}

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `d`", ss, this->countLines, this->fileName);

	dissolve.factor = StrToFloat(value, "d", this->countLines, this->fileName);
	if (needInversion)
		dissolve.factor = 1 - dissolve.factor;
}

void	MtlParser::SetShininess(std::istringstream& ss)
{
	float& shininess = this->materials[this->currentMaterial].shininess;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Ns` (exponent missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Ns`", ss, this->countLines, this->fileName);

	shininess = StrToFloat(value, "Ns", this->countLines, this->fileName);
}

void	MtlParser::SetSharpness(std::istringstream& ss)
{
	int& sharpness = this->materials[this->currentMaterial].sharpness;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `sharpness` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `sharpness`", ss, this->countLines, this->fileName);

	sharpness = StrToInt(value, "sharpness", this->countLines, this->fileName);
	if (sharpness < 0 || sharpness > 1000)
		ThrowError("Invalid value in `sharpness`, the value should be between 0 and 1000", value, this->countLines, this->fileName);
}

void	MtlParser::SetRefractiveIndex(std::istringstream& ss)
{
	float& refractiveIndex = this->materials[this->currentMaterial].refractiveIndex;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Ni` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Ni`", ss, this->countLines, this->fileName);

	refractiveIndex = StrToFloat(value, "Ni", this->countLines, this->fileName);
	if (refractiveIndex < 0.001f || refractiveIndex > 10.0f)
		ThrowError("Invalid value in `Ni`, the value should be between 0.001 and 10.0", value, this->countLines, this->fileName);
}

void	MtlParser::SetAmbiantMap(std::istringstream& ss)
{
	TextureMap& map = this->materials[this->currentMaterial].mapAmbient;

	if (statement == "decal")
		map.imfchan = ImageChan::M;

	std::string currentArg;
	while (ss >> currentArg)
	{
		if (currentArg[0] == '-')
			ParseMapOptions(currentArg, ss, map, statement);
	}
}
