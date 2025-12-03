#include "ObjParser.hpp"

void	ObjParser::FillRaw(std::ifstream& ifs)
{
	std::string	line;
	size_t		count = 0;

	while (std::getline(ifs, line))
	{
		count++;

		std::istringstream ss(line);
		std::string prefix;
		if (!(ss >> prefix))
			continue;

		if (prefix == "v")
			this->raw.vertices.emplace_back(NewVertex(ss, count));
		else if (prefix == "vt")
			this->raw.uvs.emplace_back(NewUV(ss, count));
		else if (prefix == "vn")
			this->raw.normals.emplace_back(NewNormal(ss, count));
		else if (prefix == "f")
			this->raw.faces.emplace_back(NewFace(ss, this->raw, count));
		else if (prefix == "#")
			continue;
		else
			ThrowError("Element not recognized", prefix, count);
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
