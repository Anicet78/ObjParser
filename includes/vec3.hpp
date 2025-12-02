#ifndef VEC3_HPP
# define VEC3_HPP

# include <iostream>
# include <exception>
# include "ft_math.hpp"

struct vec3 {

	float	x;
	float	y;
	float	z;

	vec3(float x, float y, float z);
	vec3(const vec3& vec) = default;

	vec3&	operator=(const vec3& vec) = default;

	bool	operator==(const vec3& vec) const;
	bool	operator!=(const vec3& vec) const;

	vec3	operator+(const vec3& vec) const;
	vec3	operator-(const vec3& vec) const;
	vec3	operator*(const vec3& vec) const;
	vec3	operator/(const vec3& vec) const;
	vec3&	operator+=(const vec3& vec);
	vec3&	operator-=(const vec3& vec);
	vec3&	operator*=(const vec3& vec);
	vec3&	operator/=(const vec3& vec);

	vec3	operator+(float value) const;
	vec3	operator-(float value) const;
	vec3	operator*(float value) const;
	vec3	operator/(float value) const;
	vec3&	operator+=(float value);
	vec3&	operator-=(float value);
	vec3&	operator*=(float value);
	vec3&	operator/=(float value);

	vec3			operator-(void) const;
	float&			operator[](int idx);
	const float&	operator[](int idx) const;

	float	dot(const vec3& vec) const;
	vec3&	normalize(void);

};

std::ostream& operator<<(std::ostream& os, const vec3& v);

#endif // VEC3_HPP

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool	vec3::operator==(const vec3& vec) const
{
	return (x == this->x && y == this->y && z == this->z);
}

bool	vec3::operator!=(const vec3& vec) const
{
	return (x != this->x || y != this->y || z != this->z);
}

vec3	vec3::operator+(const vec3& vec) const
{
	return (vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z));
}

vec3	vec3::operator-(const vec3& vec) const
{
	return (vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z));
}

vec3	vec3::operator*(const vec3& vec) const
{
	return (vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z));
}

vec3	vec3::operator/(const vec3& vec) const
{
	return (vec3(this->x / vec.x, this->y / vec.y, this->z / vec.z));
}

vec3&	vec3::operator+=(const vec3& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	return (*this);
}

vec3&	vec3::operator-=(const vec3& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	return (*this);
}

vec3&	vec3::operator*=(const vec3& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	return (*this);
}

vec3&	vec3::operator/=(const vec3& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	return (*this);
}

vec3	vec3::operator+(float value) const
{
	return (vec3(this->x + value, this->y + value, this->z + value));
}

vec3	vec3::operator-(float value) const
{
	return (vec3(this->x - value, this->y - value, this->z - value));
}

vec3	vec3::operator*(float value) const
{
	return (vec3(this->x * value, this->y * value, this->z * value));
}

vec3	vec3::operator/(float value) const
{
	return (vec3(this->x / value, this->y / value, this->z / value));
}

vec3&	vec3::operator+=(float value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	return (*this);
}

vec3&	vec3::operator-=(float value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	return (*this);
}

vec3&	vec3::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return (*this);
}

vec3&	vec3::operator/=(float value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return (*this);
}

vec3	vec3::operator-(void) const
{
	return (vec3(-this->x, -this->y, -this->z));
}

float&	vec3::operator[](int idx)
{
	if (idx < 0 || idx > 2)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : idx == 1 ? this->y : this-> z);
}

const float&	vec3::operator[](int idx) const
{
	if (idx < 0 || idx > 2)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : idx == 1 ? this->y : this-> z);
}

float vec3::dot(const vec3& vec) const
{
	return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
}

vec3& vec3::normalize(void)
{
	*this * Q_rsqrt(this->dot(*this));
	return (*this);
}

std::ostream& operator<<(std::ostream& os, const vec3& v)
{
	os << "vec4(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
