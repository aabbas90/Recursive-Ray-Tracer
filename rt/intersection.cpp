#include "intersection.h"
#include <core/assert.h>
#include <iostream>

namespace rt
{
	Intersection Intersection::failure()
	{
		return Intersection();
	}

	Intersection::Intersection(float distance, const Ray & ray, const Solid * solid, const Vector & normal)
	{
		this->distance = distance;

		// Normally the distance should always be positive!
		if (distance < 0)
		{
			std::cout << "Intersection distance less than zero!";
			throw;
		}

		// Changing the direction of normal vector towards the ray.
		Vector normalVector = normal;

		this->ray = ray;
		this->solid = solid;
		this->normalVector = normalVector;
		this->globalIntersectionPoint = ray.getPoint(distance);
		foundIntersection = true;
	}

	Point Intersection::hitPoint() const
	{
		return globalIntersectionPoint;
	}

	Vector Intersection::normal() const
	{
		return normalVector;
	}
	void Intersection::setNormal(Vector& normal)
	{
		this->normalVector = normal;
	}

	Point Intersection::local() const
	{
		return localIntersectionPoint;
	}

	// Function to set the intersecting point as in local coordinates.
	void Intersection::SetLocalIntersectingPoint(const Point& point)
	{
		this->localIntersectionPoint = point;
	}

	Intersection::operator bool()
	{
		return foundIntersection;
	}
}
