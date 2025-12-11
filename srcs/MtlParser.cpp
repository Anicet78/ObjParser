#include "MtlParser.hpp"

MtlParser::MtlParser(void)
{
	this->countLines = 0;
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
		else if (prefix == "Ka")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].ambient);
		else if (prefix == "Kd")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].diffuse);
		else if (prefix == "Ks")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].specular);
		else if (prefix == "Tf")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].transmissionFilter);
		else if (prefix == "illum")
			this->SetIllumModel(ss);
		else if (prefix == "d" || prefix == "Tr")
			this->SetDissolve(ss, prefix == "Tr");
		else if (prefix == "Ns")
			this->SetShininess(ss);
		else if (prefix == "sharpness")
			this->SetSharpness(ss);
		else if (prefix == "Ni")
			this->SetRefractiveIndex(ss);
		else if (prefix == "map_Ka")
			this->SetAmbiantMap(ss);
		else if (prefix == "map_Kd")
			this->SetDiffuseMap(ss);
		else if (prefix == "map_Ks")
			this->SetSpecularMap(ss);
		else if (prefix == "map_Ns")
			this->SetShininessMap(ss);
		else if (prefix == "map_d")
			this->SetDissolveMap(ss);
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
		ThrowError("Could not open file `" + filename + "`: " + std::strerror(errno));

	MtlParser parser;
	parser.fileName = filename;
	parser.ParseFile(ifs);

	ifs.close();
	return (parser.materials);
}
