#include "MtlParser.hpp"

MaterialList	MtlParser::ImportMtl(std::string filename)
{
	MtlParser	parser;

	std::ifstream ifs(filename);
	if (!ifs.is_open())
		ThrowError("Could not open file `" + filename + "`: " + std::strerror(ifs.rdstate()));

	ifs.close();
}