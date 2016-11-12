#include "sphere.h"
#include<core/assert.h>
#include<rt/bbox.h>
#include<rt/solids/quadric.h>

namespace rt
{
	Sphere::Sphere(const Point & center, float radius, CoordMapper * texMapper, Material * material)
	{
		this->center = center;
		this->radius = radius;
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox Sphere::getBounds() const
	{
		NOT_IMPLEMENTED;
	}

	Intersection Sphere::intersect(const Ray & ray, float previousBestDistance) const
	{
		// https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
		// Assuming ray vector is normalized
		Vector oMinusC = ray.o - center;
		float lDotoMinusC = dot(ray.d, oMinusC);
		float rightTerm = lDotoMinusC * lDotoMinusC - (ray.o - center).lensqr() + radius * radius;
		if (rightTerm < 0)
			return Intersection();		// Indicates failure

		else
		{
			float d1 = -lDotoMinusC + sqrtf(rightTerm);
			float d2 = -lDotoMinusC - sqrtf(rightTerm);
			float currentMinDistance = min(d1, d2);

			if (currentMinDistance > previousBestDistance)
			{
				return Intersection();
			}

			if (currentMinDistance < 0)
				currentMinDistance = max(d1, d2);

			if (currentMinDistance > 0 && currentMinDistance < previousBestDistance)
			{
				Point intersectionPoint = ray.getPoint(currentMinDistance);
				Vector normalVector = intersectionPoint - center;
				Intersection intersect = Intersection(currentMinDistance, ray, this, normalVector.normalize());
				intersect.SetLocalIntersectingPoint((ray.getPoint(currentMinDistance) - center).ToPoint());
				return intersect;
			}
		}

		return Intersection();
	}

	Point Sphere::sample() const
	{
		NOT_IMPLEMENTED;
	}

	float Sphere::getArea() const
	{
		return 4 * pi * radius * radius;
	}

	Quadric* Sphere::ToQuadric()
	{
		float a = 1;
		float b = 1;
		float c = 1;
		float d = 0;
		float e = 0;
		float f = 0;
		float g = -2.0 * center.x;
		float h = -2.0 * center.y;
		float i = -2.0 * center.z;
		float j = -radius * radius + center.x * center.x + center.y * center.y + center.z * center.z;

		return new Quadric(a, b, c, d, e, f, g, h, i, j, texMapper, material);
	}
}
