#pragma once
#include "float3.h"
#include "bounding_box.h"

class bound_sphere
{
public:
	bound_sphere();
	bound_sphere(const float3& c, const float3& r);

	bool contains(const float3& pt) const;
	bool contains(const bounding_box& bb) const;
public:
	float3 center;
	float3 radius;
};

