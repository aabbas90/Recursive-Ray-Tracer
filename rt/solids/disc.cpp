#include "disc.h"
#include "infiniteplane.h"
namespace rt
{
	Disc::Disc(const Point & center, const Vector & normal, float radius, CoordMapper * texMapper, Material * material)
	{
		this->center = center;
		this->normal = normal;
		this->radius = radius;
	}

	Intersection Disc::intersect(const Ray & ray, float previousBestDistance) const
	{
		InfinitePlane plane = InfinitePlane(center, normal, texMapper, material);
		if (plane.intersect(ray, previousBestDistance))
		{

		}
	}
}