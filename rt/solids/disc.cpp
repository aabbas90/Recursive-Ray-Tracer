#include "disc.h"
#include "infiniteplane.h"
#include<core/assert.h>
#include<rt/bbox.h>

namespace rt
{
	Disc::Disc(const Point & center, const Vector & normal, float radius, CoordMapper * texMapper, Material * material)
	{
		this->center = center;
		this->normal = normal;
		this->radius = radius;
		this->texMapper = texMapper;
		this->material = material;
	}

	// Check if this works!:
	// What happens when bbox has length along one dimension = 0?
	BBox Disc::getBounds() const
	{
		Vector normalizedNormal = normal.normalize();
		Vector xSpanningVector = Vector(1, 0, 0);
		Vector ySpanningVector = Vector(0, 1, 0);
		if (std::abs(dot(xSpanningVector, normalizedNormal)) != 1)
		{
			ySpanningVector = cross(normalizedNormal, xSpanningVector).normalize();
			xSpanningVector = cross(ySpanningVector, normalizedNormal).normalize();
		}
		else
		{
			xSpanningVector = cross(ySpanningVector, normalizedNormal).normalize();
			ySpanningVector = cross(normalizedNormal, xSpanningVector).normalize();
		}
		Point v1 = center + radius * xSpanningVector;
		Point v2 = center - radius * xSpanningVector;
		BBox box = BBox(min(v1, v2), max(v1, v2));
		Point v3 = center + radius * ySpanningVector;
		Point v4 = center - radius * ySpanningVector;
		box.extend(v3);
		box.extend(v4);
		return box;
	}

	Intersection Disc::intersect(const Ray & ray, float previousBestDistance) const
	{
		InfinitePlane plane = InfinitePlane(center, normal, texMapper, material);
		Intersection planeInt = plane.intersect(ray, previousBestDistance);
		
		if (planeInt)
		{
			Point intersectionPoint = planeInt.hitPoint();
			float distance2FromCentre = Vector(center - intersectionPoint).lensqr();

			if (distance2FromCentre < radius * radius)
			{
				planeInt.SetLocalIntersectingPoint((intersectionPoint - center).ToPoint());
				return planeInt;
			}
		}

		return Intersection();
	}

	Point Disc::sample() const
	{
		NOT_IMPLEMENTED;
	}

	float Disc::getArea() const
	{
		return pi * radius * radius;
	}
}