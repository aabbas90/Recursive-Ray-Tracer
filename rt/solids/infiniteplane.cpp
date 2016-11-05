#include "infiniteplane.h"

namespace rt
{
	InfinitePlane::InfinitePlane(const Point & origin, const Vector & normal, CoordMapper * texMapper, Material * material)
	{
		this->origin = origin;
		this->normal = normal;
		this->texMapper = texMapper;
		this->material = material;
	}

	Intersection InfinitePlane::intersect(const Ray & ray, float previousBestDistance) const
	{
		float denom = dot(normal, ray.d);
		if (denom > 1e-6) 
		{
			float currentDistance = dot(origin - ray.o, normal) / denom;
			if (currentDistance < previousBestDistance)
				return Intersection(currentDistance, ray, this, normal);			
		}

		return Intersection();
	}

	float InfinitePlane::getArea() const
	{
		return FLT_MAX;
	}
}