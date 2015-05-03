#include "bound_sphere.h"



bound_sphere::bound_sphere()
{
	center = 0.0;
	radius = -1.0;
}

bound_sphere::bound_sphere(const float3& c, const float3& r)
{
	center = c;
	radius = r;
}

