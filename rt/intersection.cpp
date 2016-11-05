#include "intersection.h"
#include <core/assert.h>

namespace rt
{
	Intersection Intersection::failure()
	{
		return Intersection();
	}

	Intersection::Intersection(float distance, const Ray & ray, const Solid * solid, const Vector & normal)
	{
		this->distance = distance;
		this->ray = ray;
		this->solid = solid;
		this->normalVector = normal;
		foundIntersection = true;
	}

	Point Intersection::hitPoint() const
	{
		return ray.getPoint(distance);
	}

	Vector Intersection::normal() const
	{
		return normalVector;
	}

	Point Intersection::local() const
	{
		NOT_IMPLEMENTED;
	}

	Intersection::operator bool()
	{
		return foundIntersection;
	}
}
