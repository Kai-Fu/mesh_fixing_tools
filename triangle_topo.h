#pragma once
#include "common.h"
#include "float3.h"
#include <vector>
#include <list>

class directed_edge
{
public:
	uint v0;
	uint v1;

	operator size_t() const;
	bool operator < (const directed_edge& r) const;
};

class triangle
{
public:
	uint v0;
	uint v1;
	uint v2;
	uint surface_id;

	operator size_t() const;
	bool operator < (const triangle& r) const;

	void triangle_make_faceless();
	void triangle_unify_winding();
};

struct edge_vis_flag
{
	uint e0;
	uint e1;
	uint e2;
};

class triangle_topo
{
public:
	std::vector<triangle>	triangles;
	float3					vertices;

	void make_surface_boundaries(std::vector<edge_vis_flag>& out_surface_boundaries) const;

	void make_surface_smooth_groups(std::vector<uint>& out_surface_smooth_groups) const;

	void merge_duplicated_vertices();

	void remove_duplicated_triangles();

	void merge_vertices(const uint* merge_lists);
};
