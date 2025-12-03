#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <sstream>
# include "color.hpp"
# include "Elements.hpp"

// Raw Object File
struct OBJRaw {
	std::vector<Vertex>	vertices;
	std::vector<UV>		uvs;
	std::vector<Normal>	normals;
	std::vector<Face>	faces;
};

/* struct MeshGPU {
	std::vector<Vertex>		vertices;
	std::vector<uint32_t>	indices;
}; */

// Main class
class ObjParser {

	private:
		OBJRaw	raw;

		void	FillRaw(std::ifstream& ifs);

	public:
		static void	ParseFile(std::string filename);

};

// Elements
Vertex	NewVertex(std::istringstream& ss, size_t currentLine);
UV		NewUV(std::istringstream& ss, size_t currentLine);
Normal	NewNormal(std::istringstream& ss, size_t currentLine);
Face	NewFace(std::istringstream& ss, OBJRaw& raw, size_t currentLine);

// Errors
[[noreturn]] void	ThrowError(std::string error);
[[noreturn]] void	ThrowError(std::string error, size_t line);
[[noreturn]] void	ThrowError(std::string error, std::string& token, size_t line);
[[noreturn]] void	ThrowError(std::string error, std::istringstream& ss, size_t line);

#endif // PARSER_HPP
