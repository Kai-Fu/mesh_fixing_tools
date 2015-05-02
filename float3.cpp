#include "float3.h"
#include <math.h>
#include <assert.h>
#include <algorithm>

float3::float3()
{
}

float3::float3(real single_value)
{
	x = y = z = single_value;
}

float3::float3(real _x, real _y, real _z)
{
	x = _x; y = _y; z = _z;
}

float3::float3(const real ptr[3])
{
	x = ptr[0]; y = ptr[1]; z = ptr[2];
}

real float3::length() const
{
	return math_sqrt(length_square());
}

real float3::length_square() const
{
	return x*x + y*y + z*z;
}

Axis float3::major_axis() const
{
	real vec[3] = {x, y, z};
	real* res = std::max_element(vec, vec + 3);
	return Axis((res - vec) / sizeof(vec));
}

float3 float3::operator+(const float3 & r) const
{
	return float3(x+r.x, y+r.y, z+r.z);
}

float3 float3::operator-(const float3 & r) const
{
	return float3(x - r.x, y - r.y, z - r.z);
}

float3 float3::operator*(const float3 & r) const
{
	return float3(x * r.x, y * r.y, z * r.z);
}

float3 float3::operator/(const float3 & r) const
{
	return float3(x / r.x, y / r.y, z / r.z);
}

real& float3::operator[](uint i)
{
	switch (i) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		assert(0);
		return x;
	}
}

real float3::operator[](uint i) const
{
	switch (i) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		assert(0);
		return x;
	}
}





