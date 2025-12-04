#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <sstream>
# include <algorithm>
# include <unordered_map>
# include <variant>
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
	std::vector<Point>				points;
};

// Groups
struct Group {
	std::vector<uint32_t>	faceIndices;
	std::vector<uint32_t>	lineIndices;
	std::vector<uint32_t>	pointIndices;
};

struct Object {
	std::unordered_map<std::string, Group>	groups;
	std::vector<Group*>						activeGroups;
};


/* struct MeshGPU {
	std::vector<Vertex>		vertices;
	std::vector<uint32_t>	indices;
}; */

// Main class
class ObjParser {

	private:
		ObjParser(void);
		size_t	countLines;

		void	NewObject(std::istringstream& ss);
		void	SetGroups(std::istringstream& ss);
		void	AddToGroups(std::string& prefix);
		void	FillRaw(std::ifstream& ifs);

		Vertex				NewVertex(std::istringstream& ss);
		UV					NewUV(std::istringstream& ss);
		Normal				NewNormal(std::istringstream& ss);
		ParamSpaceVertex	NewParamSpaceVertex(std::istringstream& ss);
		Face				NewFace(std::istringstream& ss);
		Line				NewLine(std::istringstream& ss);
		Point				NewPoint(std::istringstream& ss);

	public:
		OBJRaw									raw;
		std::unordered_map<std::string, Object>	objects;
		Object*									currentObject;

		static void	ParseFile(std::string filename);

};

// Errors
[[noreturn]] void	ThrowError(std::string error);
[[noreturn]] void	ThrowError(std::string error, size_t line);
[[noreturn]] void	ThrowError(std::string error, std::string& token, size_t line);
[[noreturn]] void	ThrowError(std::string error, std::istringstream& ss, size_t line);

#endif // PARSER_HPP
