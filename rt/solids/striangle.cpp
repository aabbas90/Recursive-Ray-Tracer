#include "striangle.h"
#include <core/assert.h>
#include <rt/intersection.h>

namespace rt
{
	SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper * texMapper, Material * material)
	{
		NOT_IMPLEMENTED;
	}
	SmoothTriangle::SmoothTriangle(const Point & v1, const Point & v2, const Point & v3, const Vector & n1, const Vector & n2, const Vector & n3, CoordMapper * texMapper, Material * material)
	{
		NOT_IMPLEMENTED;
	}

	Intersection SmoothTriangle::intersect(const Ray & ray, float previousBestDistance) const
	{
		NOT_IMPLEMENTED;
	}
}