#pragma once
#include "common.h"
#include "float3.h"
#include "bounding_box.h"
#include <vector>
#include <memory>
#include <assert.h>

class point3_accel
{
public:
	point3_accel();
	virtual ~point3_accel();

	void initialize(const float3* pt_array, uint cnt);

	void search(const float3& pos, std::vector<uint>& out_result) const;


protected:
	struct kd_node
	{
		struct limb
		{
			real split_position;
			uint h_left_child;
			uint h_right_child;

			uint point_idx_start;
			uint point_count;
		};

		struct leaf
		{
			uint point_idx_start;
			uint point_count;
			bounding_box bbox;
		};
		
		uint flag;
		

		limb& as_limb() 
		{ 
			assert((flag & is_leaf_mask) == 0);
			return *(limb*)(this + 1); 
		}

		const limb& as_limb() const
		{
			assert((flag & is_leaf_mask) == 0);
			return *(limb*)(this + 1);
		}

		leaf& as_leaf() 
		{ 
			assert(flag & is_leaf_mask);
			return *(leaf*)(this + 1); 
		}

		const leaf& as_leaf() const
		{
			assert(flag & is_leaf_mask);
			return *(leaf*)(this + 1);
		}

	};

	const static uint is_leaf_mask = 0x0004;
	const static uint limb_node_size = sizeof(kd_node) + sizeof(kd_node::limb);
	const static uint leaf_node_size = sizeof(kd_node) + sizeof(kd_node::leaf);
	std::vector<byte> mNodeData;
	typedef uint node_handle;

	node_handle split_node(uint start_idx, uint count, uint depth = 0);
	kd_node* get_kd_node(node_handle handle);
	const kd_node* get_kd_node(node_handle handle) const;
	void search_node(const float3& unified_pos, node_handle node, std::vector<uint>& out_result) const;

private:
	struct indexed_point3
	{
		float3 point;
		uint index;
	};
	std::vector<indexed_point3>	mpUnifiedPoints;
	bounding_box				mOrigBBox;
	kd_node						mRootNode;

	uint						mLeafThreshold;
	uint						mDepthThreshold;

};

