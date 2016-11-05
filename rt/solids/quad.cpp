#include "quad.h"
#include <rt/intersection.h>
#include <core/assert.h>

namespace rt
{
	Quad::Quad(const Point & v1, const Vector & span1, const Vector & span2, CoordMapper * texMapper, Material * material)
	{
		this->v1 = v1;
		this->span1 = span1;
		this->span2 = span2;
	}

	Intersection Quad::intersect(const Ray & ray, float previousBestDistance) const
	{
		NOT_IMPLEMENTED;
	}
]
