#pragma once
#include "float3.h"

class bounding_box
{
public:
	bounding_box();
	bounding_box(const float3& pmin, const float3& pmax);

	bool contains(const float3& pt) const;
	bool contains(const bounding_box& bb) const;
	bool is_overlaping(const bounding_box& bb) const;

	float3 center() const;
	float3 length() const;
	bool empty() const;
	Axis major_axis() const;

	void include_points(const float3* pt_array, uint cnt, uint step = sizeof(float3));

	float3 to_unified_space(const float3& pt) const;
	void to_unified_space(float3* pt_array, uint cnt, uint step) const;
	float3 from_unified_space(const float3& pt) const;
	void from_unified_space(float3* pt_array, uint cnt, uint step) const;
public:
	float3 min;
	float3 max;
};

