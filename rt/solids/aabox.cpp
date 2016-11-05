#include "aabox.h"
#include <core/assert.h>

namespace rt
{
	AABox::AABox(const Point & corner1, const Point & corner2, CoordMapper * texMapper, Material * material)
	{
		this->corner1 = corner1;
		this->corner2 = corner2;
	}

	Intersection AABox::intersect(const Ray & ray, float previousBestDistance) const
	{
		NOT_IMPLEMENTED;
	}
}
