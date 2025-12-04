#include "ObjParser.hpp"

ObjParser::ObjParser(void)
{
	this->activeGroups.emplace_back(&this->groups["default"]);
	this->countLines = 0;
}

void	ObjParser::SetGroups(std::istringstream& ss)
{
	this->activeGroups.clear();

	std::string	currentGroup;
	while (ss >> currentGroup)
		this->activeGroups.emplace_back(&this->groups[currentGroup]);
	if (this->activeGroups.size() == 0)
		this->activeGroups.emplace_back(&this->groups["default"]);
}

void	ObjParser::AddToGroups(std::string& prefix)
{
	std::variant<
		std::vector<Face>*,
		std::vector<Line>*,
		std::vector<Point>*
	> vec;

	if (prefix == "f")
		vec = &raw.faces;
	else if (prefix == "l")
		vec = &raw.lines;
	else if (prefix == "p")
		vec = &raw.points;
	else
		return;

	for (Group* group : activeGroups) {
		std::visit([&group](auto* v){
			group->faceIndices.push_back(v->size());
		}, vec);
	}
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
		else if (prefix == "g")
			this->SetGroups(ss);
		else if (prefix == "#")
			continue;
		else
			ThrowError("Element not recognized", prefix, this->countLines);
		this->AddToGroups(prefix);
	}
}

void	ObjParser::ParseFile(std::string filename)
{
	ObjParser	parser;

	std::ifstream ifs(filename);
	if (!ifs.is_open())
		ThrowError("Could not open file `" + filename + "`: " + std::strerror(ifs.rdstate()));

	parser.FillRaw(ifs);

	ifs.close();
}
