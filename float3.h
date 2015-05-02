#pragma once
#include "common.h"

class float3
{
public:
	float3();
	float3(real single_value);
	float3(real x, real y, real z);
	float3(const real ptr[3]);

	real length() const;
	real length_square() const;
	Axis major_axis() const;

	float3 operator + (const float3& r) const;
	float3 operator - (const float3& r) const;
	float3 operator * (const float3& r) const;
	float3 operator / (const float3& r) const;

	real& operator [](uint i);
	real operator [](uint i) const;

public:
	real x;
	real y;
	real z;
};

