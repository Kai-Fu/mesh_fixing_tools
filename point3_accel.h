#pragma once
#include "common.h"
#include "float3.h"
#include "bounding_box.h"
#include <vector>
#include <memory>

class point3_accel
{
public:
	point3_accel();
	virtual ~point3_accel();

	void initialize(const float3* pt_array);

	void search(const float3& pos, float radius, std::vector<uint>& out_result) const;

	void search(const float3& pos, std::vector<uint>& out_result) const;


protected:
	struct kd_node
	{
		uint flag;

		struct limb
		{
			real split_position;
			uint left_child_idx;
			uint right_child_idx;

			uint point_idx_start;
			uint point_count;
		};

		struct leaf
		{
			uint point_idx_start;
			uint point_count;
			bounding_box bbox;
		};

		union
		{
			limb as_limb;
			leaf as_leaf;
		} data;
		
	};

	struct kd_leaf
	{
		uint point_idx_start;
		uint point_count;
		bounding_box bbox;
	};


	kd_node split_node(uint start_idx, uint count);

private:
	std::vector<float3>			mpUnifiedPoints;
	bounding_box				mOrigBBox;
	std::unique_ptr<kd_node>	mRootNode;

	uint						mLeafThreshold;
	uint						mDepthThreshold;

};

