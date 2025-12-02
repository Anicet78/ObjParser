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

Face	NewFace(std::istringstream& ss, size_t currentLine)
{

}