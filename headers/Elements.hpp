#ifndef ELEMENTS_HPP
# define ELEMENTS_HPP

# include <vector>
# include "vec3.hpp"
# include "vec4.hpp"

typedef vec4 Vertex;
typedef vec3 UV;
typedef vec3 Normal;
typedef vec3 ParamSpaceVertex;

struct FaceElement {
	uint32_t	vIndex;
	uint32_t	vtIndex;
	uint32_t	vnIndex;

	FaceElement(uint32_t v, uint32_t vt, uint32_t vn) {
		this->vIndex = v; this->vtIndex = vt; this->vnIndex = vn;
	}
};

struct Face {
	std::vector<FaceElement>	elements;
	std::string					materialName;
	int							smoothingGroupIndex;
};

struct LineElement {
	uint32_t	vIndex;
	uint32_t	vtIndex;

	LineElement(uint32_t v, uint32_t vt) {
		this->vIndex = v; this->vtIndex = vt;
	}
};

struct Line {
	std::vector<LineElement> elements;
};

struct Point {
	std::vector<uint32_t> vertices;
};

template <typename T>
uint32_t	GetIndex(std::vector<T>& vector, int index)
{
	if (index < 0)
	{
		if (static_cast<int>(vector.size()) < -index)
			return (0);
		return (vector.size() - (-index - 1));
	}
	return (static_cast<int>(vector.size()) < index ? 0 : index);
}

#endif // !ELEMENTS_HPP
