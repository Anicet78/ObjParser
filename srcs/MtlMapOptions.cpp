#include "MtlParser.hpp"

bool	MtlParser::ParseOnOff(std::istringstream& ss, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option in `" + statement + "` (on | off)", option, this->countLines, this->fileName);
	if (value == "on")
		return (true);
	else if (value == "off")
		return (false);
	else
		ThrowError("Invalid argument in `" + statement + "` (on | off)", option, this->countLines, this->fileName);
}

void	MtlParser::SetMapModifiers(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option in `" + statement + "` (base, gain)", option, this->countLines, this->fileName);
	map.base = StrToFloat(value, statement, this->countLines, this->fileName);
	if (!(ss >> value))
		ThrowError("Missing argument for option in `" + statement + "` (base, gain)", option, this->countLines, this->fileName);
	map.gain = StrToFloat(value, statement, this->countLines, this->fileName);
}

void	MtlParser::ParseOST(std::istringstream& ss, vec3& vec, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option in `" + statement + "` (u, [v, w])", option, this->countLines, this->fileName);
	vec.x = StrToFloat(value, statement, this->countLines, this->fileName);
	if (!ss.eof() && ss >> value)
		vec.y = StrToFloat(value, statement, this->countLines, this->fileName);
	if (!ss.eof() && ss >> value)
		vec.z = StrToFloat(value, statement, this->countLines, this->fileName);
}

void	MtlParser::SetResolution(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option in `" + statement + "` (resolution)", option, this->countLines, this->fileName);
	map.resolution = StrToInt(value, statement, this->countLines, this->fileName);
}

void	MtlParser::ParseMapOptions(std::string& option, std::istringstream& ss, TextureMap& map, std::string& statement)
{
	if (option == "-blendu")
		map.blendu = this->ParseOnOff(ss, option, statement);
	else if (option == "-blendv")
		map.blendv = this->ParseOnOff(ss, option, statement);
	else if (option == "-cc")
		map.cc = this->ParseOnOff(ss, option, statement);
	else if (option == "-clamp")
		map.clamp = this->ParseOnOff(ss, option, statement);
	else if (option == "-mm")
		this->SetMapModifiers(ss, map, option, statement);
	else if (option == "-o")
		this->ParseOST(ss, map.offset, option, statement);
	else if (option == "-s")
		this->ParseOST(ss, map.scale, option, statement);
	else if (option == "-t")
		this->ParseOST(ss, map.turbulence, option, statement);
	else if (option == "-texres")
		this->SetResolution(ss, map, option, statement);
	else
		ThrowError("Option not recognized in `" + statement + "`", option, this->countLines, this->fileName);
}
