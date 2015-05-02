#pragma once

enum Axis
{
	X = 0, 
	Y = 1, 
	Z = 2,
	Mask = 0x0003
};

typedef unsigned int uint;

#ifdef WANT_DOUBLE_PRECISION
	typedef double real;
	#define math_sqrt sqrt
#else
	typedef float real;
	#define math_sqrt sqrtf
#endif

template <typename ValueType>
ValueType compute_average(const ValueType* value_array, uint count, ValueType* temp_buf)
{
	if (count == 1)
		return value_array[0];

	if (temp_buf == nullptr)
		temp_buf = new ValueType[(count + 1) / 2];

	const ValueType* src_value = value_array;
	ValueType* dst_value = temp_buf;
	uint it_cnt = count;

	do {
		for (uint i = 0; i < it_cnt; i += 2) {
			dst_value[it_cnt / 2] = (src_value[i] + src_value[i + 1]) / 2.0f;
		}
	} while (it_cnt > 0);

	return temp_buf[0];
}