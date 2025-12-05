#include "MtlParser.hpp"

MtlParser::MtlParser(void)
{
	this->countLines = 0;
}

void	MtlParser::NewMaterial(std::istringstream& ss)
{
	std::string materialName = "";
	std::string namePart;
	while (ss >> namePart)
	{
		materialName += namePart;
		materialName += " ";
	}

	if (materialName == "")
		ThrowError("You must provide a name for the material in `newmtl`", this->countLines, this->fileName);
	materialName.erase(materialName.back());

	this->materials[namePart];
	this->currentMaterial = materialName;
}

void	MtlParser::ParseFile(std::ifstream& ifs)
{
	std::string	line;

	while (std::getline(ifs, line)) {
		this->countLines++;

		std::istringstream ss(line);
		std::string prefix;
		if (!(ss >> prefix))
			continue;

		if (prefix == "newmtl")
			this->NewMaterial(ss);
		else if (prefix == "#")
			continue;
		else // May skip instead later
			ThrowError("Element not recognized", prefix, this->countLines, this->fileName);
	}
}

MaterialList	MtlParser::ImportMtl(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
		ThrowError("Could not open file `" + filename + "`: " + std::strerror(ifs.rdstate()));

	MtlParser parser;
	parser.fileName = filename;
	parser.ParseFile(ifs);

	ifs.close();
	return (parser.materials);
}