#include "point3_accel.h"
#include <algorithm>


point3_accel::point3_accel()
{
	// Some magic number based on experience
	mLeafThreshold = 123;
	mDepthThreshold = 17;
}


point3_accel::~point3_accel()
{
}

void point3_accel::initialize(const float3 * pt_array, uint cnt)
{
	mNodeData.clear();
	mNodeData.reserve(cnt * leaf_node_size);

	mOrigBBox = bounding_box();
	mOrigBBox.include_points(pt_array, cnt);
	mpUnifiedPoints.resize(cnt);
	for (uint i = 0; i < cnt; ++i) {
		mpUnifiedPoints[i].point = mOrigBBox.to_unified_space(pt_array[i]);
		mpUnifiedPoints[i].index = i;
	}
	
	node_handle h_root = split_node(0, cnt);
	mRootNode = *get_kd_node(h_root);
}

void point3_accel::search(const float3& pos, std::vector<uint>& out_result) const
{

}

point3_accel::node_handle point3_accel::split_node(uint start_idx, uint count, uint depth)
{
	class PartitionFunctor {
	public:
		Axis split_axis;
		real split_pos;

		bool operator () (const indexed_point3& ref) {
			return ref.point[split_axis] < split_pos;
		}
	};

	indexed_point3* p_begin = &mpUnifiedPoints[start_idx];
	indexed_point3* p_end = p_begin + count;
	bounding_box bbox;
	bbox.include_points(&p_begin->point, count, sizeof(indexed_point3));
	if (count <= mLeafThreshold) {
		node_handle node_handle = mNodeData.size();
		mNodeData.resize(mNodeData.size() + leaf_node_size);
		kd_node* leafNode = (kd_node*)&mNodeData[node_handle];
		leafNode->flag = is_leaf_mask;
		kd_node::leaf& leaf = leafNode->as_leaf();
		leaf.point_idx_start = start_idx;
		leaf.point_count = count;
		leaf.bbox = bbox;
		return node_handle;
	}
	else {
		Axis split_axis = bbox.major_axis();
		real split_pos = (bbox.min[split_axis] + bbox.max[split_axis]) * 0.5f;
		PartitionFunctor split_functor = { split_axis, split_pos };
		indexed_point3* r_start = std::partition(p_begin, p_end, split_functor);
		uint l_cnt = (r_start - p_begin) / sizeof(indexed_point3);
		uint r_cnt = count - l_cnt;

		node_handle node_handle = mNodeData.size();
		mNodeData.resize(mNodeData.size() + limb_node_size);
		kd_node* limbNode = (kd_node*)&mNodeData[node_handle];
		limbNode->flag = split_axis;
		kd_node::limb& limb = limbNode->as_limb();
		limb.split_position = split_pos;
		limb.point_idx_start = start_idx;
		limb.point_count = count;
		limb.h_left_child = split_node(start_idx, l_cnt, depth + 1);
		limb.h_right_child = split_node(start_idx + l_cnt, r_cnt, depth + 1);
		return node_handle;
	}
}

point3_accel::kd_node * point3_accel::get_kd_node(node_handle handle)
{
	kd_node* result = (kd_node*)&mNodeData[handle];
	return result;
}

const point3_accel::kd_node * point3_accel::get_kd_node(node_handle handle) const
{
	const kd_node* result = (const kd_node*)&mNodeData[handle];
	return result;
}

void point3_accel::search_node(const float3& unified_pos, node_handle node, std::vector<uint>& out_result) const
{
	const kd_node* pNode = get_kd_node(node);
	if (pNode->flag & is_leaf_mask) {
		const kd_node::leaf& l = pNode->as_leaf();
		if (l.bbox.contains(unified_pos)) {
			for (uint i = l.point_idx_start; i < l.point_idx_start + l.point_count; ++i) {
				if ((mpUnifiedPoints[i].point - unified_pos).length_square() <= (epsilon_real*epsilon_real))
					out_result.push_back(mpUnifiedPoints[i].index);
			}
		}
	}
	else {
		const kd_node::limb& l = pNode->as_limb();
		if (unified_pos[pNode->flag & Axis::Mask] <= l.split_position)
			search_node(unified_pos, l.h_left_child, out_result);
		else 
			search_node(unified_pos, l.h_right_child, out_result);
	}
}
