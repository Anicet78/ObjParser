#include "ObjParser.hpp"

ObjParser::ObjParser(void)
{
	this->countLines = 0;
	this->currentObject = &this->objects["default"];
	this->currentObject->activeGroups.emplace_back(&this->currentObject->groups["default"]);
	this->currentSmoothingGroup = 0;
	this->currentMergingGroup = -1;
	this->currentMergingResolution = 0;
}

void	ObjParser::AddMaterialList(std::istringstream& ss)
{
	std::string mtlFileName;
	while (ss >> mtlFileName)
	{
		MaterialList newMaterialList = MtlParser::ImportMtl(mtlFileName);
	}
	if (this->materials.size() == 0)
		ThrowError("Not enough arguments in `mtllib` ('mtlFileName', [...])", this->fileName);
}

void	ObjParser::FillRaw(std::ifstream& ifs)
{
	std::string	line;

	while (std::getline(ifs, line)) {
		this->countLines++;

		std::istringstream ss(line);
		std::string prefix;
		if (!(ss >> prefix))
			continue;

		if (prefix == "v")
			this->raw.vertices.emplace_back(NewVertex(ss));
		else if (prefix == "vt")
			this->raw.uvs.emplace_back(NewUV(ss));
		else if (prefix == "vn")
			this->raw.normals.emplace_back(NewNormal(ss));
		else if (prefix == "vp")
			this->raw.paramSpaceVertices.emplace_back(NewParamSpaceVertex(ss));
		else if (prefix == "f")
			this->raw.faces.emplace_back(NewFace(ss));
		else if (prefix == "l")
			this->raw.lines.emplace_back(NewLine(ss));
		else if (prefix == "p")
			this->raw.points.emplace_back(NewPoint(ss));
		else if (prefix == "mtllib")
			this->AddMaterialList(ss);
		else if (prefix == "o")
			this->SetObject(ss);
		else if (prefix == "g")
			this->SetGroups(ss);
		else if (prefix == "s")
			this->SetSmoothingGroup(ss);
		else if (prefix == "mg")
			this->SetMergingGroup(ss);
		else if (prefix == "#")
			continue;
		else // May skip instead later
			ThrowError("Element not recognized", prefix, this->countLines, this->fileName);
		this->AddToGroups(prefix);
	}
}

void	ObjParser::ParseFile(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
		ThrowError("Could not open file `" + filename + "`: " + std::strerror(ifs.rdstate()));
	this->fileName = filename;

	this->FillRaw(ifs);

	ifs.close();
}
