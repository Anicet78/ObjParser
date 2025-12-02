#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <fstream>
# include <sstream>
# include "color.hpp"
# include "vec2.hpp"
# include "vec3.hpp"
# include "vec4.hpp"

typedef vec4 Vertex;
typedef vec3 UV;
typedef vec3 Normal;

struct FaceElement {

};

struct Face {
	std::vector<FaceElement> elements;
};

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

class ObjParser {

	private:
		OBJRaw	raw;

		void	FillRaw(std::ifstream& ifs);

	public:
		static void	ParseFile(std::string filename);

};

Vertex	NewVertex(std::istringstream& ss, size_t currentLine);
UV		NewUV(std::istringstream& ss, size_t currentLine);
Normal	NewNormal(std::istringstream& ss, size_t currentLine);
Face	NewFace(std::istringstream& ss, size_t currentLine);
void	ThrowError(std::string error);
void	ThrowError(std::string error, size_t line);
void	ThrowError(std::string error, std::istringstream& ss, size_t line);

#endif // PARSER_HPP