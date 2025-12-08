#include "MtlParser.hpp"

Material::Material(void)
{
}

void	MtlParser::NewMaterial(std::istringstream& ss)
{
	std::string materialName = "";
	if (!(ss >> materialName) || materialName == "")
		ThrowError("You must provide a name for the material in `newmtl`", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Materials can only have one name and it cannot contains blank in `newmtl`", ss, this->countLines, this->fileName);

	this->materials[materialName];
	this->currentMaterial = materialName;
}

void	MtlParser::ParseColor(std::istringstream& ss, std::string statement, ParsedColor& color)
{
	std::string token;
	if (!(ss >> token))
		ThrowError("Not enough arguments in `" + statement + "`", this->countLines, this->fileName);

	float r, g, b;

	if (token == "spectral")
	{
		color.format = ColorFormat::Spectral;
		ss >> token;
		if (ss.eof())
			ThrowError("Not enough arguments in `" + statement + "`spectral` (file.rfl, [factor])", this->countLines, this->fileName);
		color.spectralFile = token;
		ss >> token;
		if (!ss.eof())
			color.spectralFactor = StrToFloat(token, "" + statement + " spectral", this->countLines, this->fileName);
	}
	if (token == "xyz")
	{
		if (!(ss >> token));
			ThrowError("Not enough arguments in `" + statement + " xyz` (x, [y, z])", this->countLines, this->fileName);
		r = StrToFloat(token, statement + " xyz", this->countLines, this->fileName);
		color.format = ColorFormat::XYZ;
	}
	else
	{
		r = StrToFloat(token, statement, this->countLines, this->fileName);
		color.format = ColorFormat::RGB;
	}

	ss >> token;
	if (!ss.eof())
		g = StrToFloat(token, statement, this->countLines, this->fileName);
	else
		g = r;

	if (ss.eof() && ss >> token && !ss.eof())
		b = StrToFloat(token, statement, this->countLines, this->fileName);
	else
		b = r;
	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `" + statement + "`", this->countLines, this->fileName);
	color.rgb = vec3(r, g, b);
}

void	MtlParser::SetIllumModel(std::istringstream& ss)
{
	std::string value;
	ss >> value;

	int illum = StrToInt(value, "illum", this->countLines, this->fileName);
	if (illum < 0 || illum > 10)
		ThrowError("Invalid value in `illum`, the number should be between 0 and 10", value, this->countLines, this->fileName);

	this->materials[this->currentMaterial].illuminationModel = illum;
}
