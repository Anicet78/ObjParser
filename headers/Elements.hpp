#ifndef ELEMENTS_HPP
# define ELEMENTS_HPP

# include <vector>
# include "vec2.hpp"
# include "vec3.hpp"
# include "vec4.hpp"

typedef vec4 Vertex;
typedef vec3 UV;
typedef vec3 Normal;
typedef vec3 ParamSpaceVertex;

struct FaceElement {
	uint32_t	v_indice;
	uint32_t	vt_indice;
	uint32_t	vn_indice;

	FaceElement(uint32_t v, uint32_t vt, uint32_t vn) {
		this->v_indice = v; this->vt_indice = vt; this->vn_indice = vn;
	}
};

struct Face {
	std::vector<FaceElement> elements;
};

struct LineElement {
	uint32_t	v_indice;
	uint32_t	vt_indice;

	LineElement(uint32_t v, uint32_t vt) {
		this->v_indice = v; this->vt_indice = vt;
	}
};

struct Line {
	std::vector<LineElement> elements;
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

#endif // ELEMENTS_HPP
