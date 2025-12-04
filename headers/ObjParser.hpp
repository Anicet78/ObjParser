#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <sstream>
# include "color.hpp"
# include "Elements.hpp"

// Raw Object File
struct OBJRaw {
	std::vector<Vertex>				vertices;
	std::vector<UV>					uvs;
	std::vector<Normal>				normals;
	std::vector<ParamSpaceVertex>	paramSpaceVertices;
	std::vector<Face>				faces;
	std::vector<Line>				lines;
};

/* struct MeshGPU {
	std::vector<Vertex>		vertices;
	std::vector<uint32_t>	indices;
}; */

// Main class
class ObjParser {

	private:
		OBJRaw	raw;
		size_t	countLines = 0;

		void	FillRaw(std::ifstream& ifs);

		Vertex				NewVertex(std::istringstream& ss);
		UV					NewUV(std::istringstream& ss);
		Normal				NewNormal(std::istringstream& ss);
		ParamSpaceVertex	NewParamSpaceVertex(std::istringstream& ss);
		Face				NewFace(std::istringstream& ss);
		Line				NewLine(std::istringstream& ss);

	public:
		static void	ParseFile(std::string filename);

};

// Errors
[[noreturn]] void	ThrowError(std::string error);
[[noreturn]] void	ThrowError(std::string error, size_t line);
[[noreturn]] void	ThrowError(std::string error, std::string& token, size_t line);
[[noreturn]] void	ThrowError(std::string error, std::istringstream& ss, size_t line);

#endif // PARSER_HPP
