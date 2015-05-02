#include "bounding_box.h"


bounding_box::bounding_box()
{
}

bounding_box::bounding_box(const float3 & pmin, const float3 & pmax)
{
}

bool bounding_box::contains(const float3 & pt) const
{
	return false;
}

bool bounding_box::contains(const bounding_box & bb) const
{
	return false;
}

bool bounding_box::is_overlaping(const bounding_box & bb) const
{
	return false;
}

float3 bounding_box::center() const
{
	return (min + max) * 0.5f;
}

float3 bounding_box::length() const
{
	return max - min;
}

bool bounding_box::empty() const
{
	return max.x < min.x || max.y < min.y || max.z < min.z;
}

Axis bounding_box::major_axis() const
{
	float3 len = length();
	return len.major_axis();
}

void bounding_box::include_points(const float * pt_array, uint cnt)
{
}

float3 bounding_box::to_unified_space(const float3 & pt) const
{
	float3 c = center();
	float3 half_len = length() * 0.5;
	return (pt - c) / half_len;
}

float3 bounding_box::from_unified_space(const float3 & pt) const
{
	float3 c = center();
	float3 half_len = length() * 0.5;
	return pt * half_len + c;
}


