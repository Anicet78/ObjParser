#include "ObjParser.hpp"

Vertex	NewVertex(std::istringstream& ss, size_t currentLine)
{
	float x, y, z, w = 1.0;
	if (!(ss >> x) || !(ss >> y) || !(ss >> z))
	{
		if (ss.eof())
			ThrowError("Not enough arguments in `v` (x, y, z, [w])", currentLine);
		else
			ThrowError("Invalid coordinate argument in `v`", ss , currentLine);
	}
	if (!ss.eof() && !(ss >> w))
		ThrowError("Invalid scale argument in `v`", ss , currentLine);
	if (!ss.eof())
		ThrowError("Too many arguments in `v`", currentLine);
	return (Vertex(x, y, z, w));
}

UV	NewUV(std::istringstream& ss, size_t currentLine)
{
	float u, v = 0, w = 0;
	if (ss.eof())
		ThrowError("Not enough argument in `vt` (u, [v, w])", currentLine);
	if (!(ss >> u))
		ThrowError("Invalid coordinate argument in `vt`", ss, currentLine);
	if (!ss.eof() && !(ss >> v))
		ThrowError("Invalid coordinate argument in `vt`", ss, currentLine);
	if (!ss.eof() && !(ss >> w))
		ThrowError("Invalid coordinate argument in `vt`", ss, currentLine);
	if (!ss.eof())
		ThrowError("Too many arguments in `vt`", currentLine);
	if (u < 0 || u > 1)
		ThrowError("Invalid u coordinate in `vt`, every coordinates should be in [0,1]", currentLine);
	if (v < 0 || v > 1)
		ThrowError("Invalid v coordinate in `vt`, every coordinates should be in [0,1]", currentLine);
	if (w < 0 || w > 1)
		ThrowError("Invalid w coordinate in `vt`, every coordinates should be in [0,1]", currentLine);
	return (UV(u, v, w));
}

Normal	NewNormal(std::istringstream& ss, size_t currentLine)
{
	float x, y, z;
	if (!(ss >> x) || !(ss >> y) || !(ss >> z))
	{
		if (ss.eof())
			ThrowError("Not enough arguments in `vn` (x, y, z)", currentLine);
		else
			ThrowError("Invalid normal argument in `vn`", ss , currentLine);
	}
	if (!ss.eof())
		ThrowError("Too many arguments in `vt`", currentLine);
	return (Normal(x, y, z).normalize());
}

Face	NewFace(std::istringstream& ss, OBJRaw& raw, size_t currentLine)
{
	Face face;
	std::string	currentFace;
	while (ss >> currentFace)
	{
		uint32_t v_indice, vt_indice = 0, vn_indice = 0;
		if (std::getline(ss, currentFace, '/'))
		{
			if (currentFace.empty())
				ThrowError("No vertex indice defined in `f`", ss, currentLine);
			int v = std::stoi(currentFace);
			if (v == 0)
				ThrowError("Vertex indice must be referenced by its relative position (1-based) and thus cannot be '0' in `f`", ss, currentLine);
			v_indice = GetIndex(raw.vertices, v);
			if (v_indice == 0)
				ThrowError("Vertex indice " + currentFace + " not found in the vertices list in `f`, the vertices used must be declared before the face declaration", currentLine);
		}
		if (std::getline(ss, currentFace, '/') && !currentFace.empty())
		{
			int vt = std::stoi(currentFace);
			if (vt == 0)
				ThrowError("Texture indice must be referenced by its relative position (1-based) and thus cannot be '0' in `f`", ss, currentLine);
			vt_indice = GetIndex(raw.uvs, vt);
			if (vt_indice == 0)
				ThrowError("Texture indice " + currentFace + " not found in the uvs list in `f`, the uvs used must be declared before the face declaration", currentLine);
		}
		if (std::getline(ss, currentFace, '/') && !currentFace.empty())
		{
			int vn = std::stoi(currentFace);
			if (vn == 0)
				ThrowError("Normal indice must be referenced by its relative position (1-based) and thus cannot be '0' in `f`", ss, currentLine);
			vn_indice = GetIndex(raw.normals, vn);
			if (vn_indice == 0)
				ThrowError("Normal indice " + currentFace + " not found in the normals list in `f`, the normals used must be declared before the face declaration", currentLine);
		}
		face.elements.emplace_back(FaceElement(v_indice, vt_indice, vn_indice));
	}
	if (face.elements.size() < 3)
		ThrowError("Not enough arguments in `f`, not enough vertices given (should be at least 3)", currentLine);
	return (face);
}
