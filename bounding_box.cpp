#include "bounding_box.h"
#include "float.h"
#include <algorithm>

bounding_box::bounding_box()
{
	min = float3(FLT_MAX);
	max = float3(-FLT_MAX);
}

bounding_box::bounding_box(const float3 & pmin, const float3 & pmax)
{
	min = pmin;
	max = pmax;
}

bool bounding_box::contains(const float3 & pt) const
{
	return	
		pt.x >= min.x && pt.x <= max.x &&
		pt.y >= min.y && pt.y <= max.y &&
		pt.z >= min.z && pt.z <= max.z;
}

bool bounding_box::contains(const bounding_box & bb) const
{
	return 
		min.x <= bb.min.x && max.x >= bb.max.x &&
		min.y <= bb.min.y && max.y >= bb.max.y &&
		min.z <= bb.min.z && max.z >= bb.max.z;
}

bool bounding_box::is_overlaping(const bounding_box & bb) const
{
	bool is_out =
		min.x > bb.max.x && max.x < bb.min.x &&
		min.y > bb.max.y && max.y < bb.min.y &&
		min.z > bb.max.z && max.z < bb.min.z;
	return !is_out;
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

void bounding_box::include_points(const float3* pt_array, uint cnt, uint step)
{
	const byte* p_start = (const byte*)pt_array;
	for (uint i = 0; i < cnt; ++i) {
		const float3& cur = *(const float3*)(p_start + step * i);
		min.x = std::min(min.x, cur.x);
		min.y = std::min(min.x, cur.y);
		min.z = std::min(min.x, cur.z);

		max.x = std::max(max.x, cur.x);
		max.y = std::max(max.x, cur.y);
		max.z = std::max(max.x, cur.z);
	}
}

float3 bounding_box::to_unified_space(const float3 & pt) const
{
	float3 c = center();
	float3 half_len = length() * 0.5;
	return (pt - c) / half_len;
}

void bounding_box::to_unified_space(float3 * pt_array, uint cnt, uint step) const
{
	float3 c = center();
	float3 half_len = length() * 0.5;
	byte* p_start = (byte*)pt_array;
	for (uint i = 0; i < cnt; ++i) {
		float3& cur = *(float3*)(p_start + step * i);
		cur = (cur - c) / half_len;
	}
}

float3 bounding_box::from_unified_space(const float3 & pt) const
{
	float3 c = center();
	float3 half_len = length() * 0.5;
	return pt * half_len + c;
}

void bounding_box::from_unified_space(float3 * pt_array, uint cnt, uint step) const
{
	float3 c = center();
	float3 half_len = length() * 0.5;
	byte* p_start = (byte*)pt_array;
	for (uint i = 0; i < cnt; ++i) {
		float3& cur = *(float3*)(p_start + step * i);
		cur = cur * half_len + c;
	}
}


