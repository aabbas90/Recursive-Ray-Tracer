#include "aabox.h"
#include <core/assert.h>

namespace rt
{
	AABox::AABox(const Point & corner1, const Point & corner2, CoordMapper * texMapper, Material * material)
	{
		this->minCorner = min(corner1, corner2);
		this->maxCorner = max(corner1, corner2);
		this->texMapper = texMapper;
		this->material = material;
	}

	// Idea adapted from:
	// http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	Intersection AABox::intersect(const Ray & ray, float previousBestDistance) const
	{
		float minT, maxT;
		Vector minTnormal = Vector(1, 0, 0);
		Vector maxTnormal = Vector(1, 0, 0);

		float tx0 = (minCorner.x - ray.o.x) / ray.d.x;
		float tx1 = (maxCorner.x - ray.o.x) / ray.d.x;

		if (tx0 < tx1)
		{
			minT = tx0;
			maxT = tx1;
		}

		else
		{
			minT = tx1;
			maxT = tx0;
		}

		float ty0 = (minCorner.y - ray.o.y) / ray.d.y;
		float ty1 = (maxCorner.y - ray.o.y) / ray.d.y;

		float tyMin = min(ty0, ty1);
		float tyMax = max(ty0, ty1);

		if ((minT > tyMax) || (tyMin > maxT))
			return Intersection();

		if (tyMin > minT)
		{
			minT = tyMin;
			minTnormal = Vector(0, 1, 0);
		}

		if (tyMax < maxT)
		{
			maxT = tyMax;
			maxTnormal = Vector(0, 1, 0);
		}

		float tz0 = (minCorner.z - ray.o.z) / ray.d.z;
		float tz1 = (maxCorner.z - ray.o.z) / ray.d.z;

		float tzMin = min(tz0, tz1);
		float tzMax = max(tz0, tz1);

		if ((minT > tzMax) || (tzMin > maxT))
			return Intersection();

		if (tzMin > minT)
		{
			minT = tzMin;
			minTnormal = Vector(0, 0, 1);
		}

		if (tzMax < maxT)
		{
			maxT = tzMax;
			maxTnormal = Vector(0, 0, 1);
		}

		Intersection intersect = Intersection();
		if (minT < maxT)
		{
			// Assuming that the negative distance means no valid intersection
			if (minT > 0 && minT < previousBestDistance)
			{
				intersect = Intersection(minT, ray, this, minTnormal);
				intersect.SetLocalIntersectingPoint((ray.getPoint(minT) - minCorner).ToPoint());
			}

			else if (maxT > 0 && maxT < previousBestDistance)
			{
				intersect = Intersection(maxT, ray, this, maxTnormal);
				intersect.SetLocalIntersectingPoint((ray.getPoint(maxT) - minCorner).ToPoint());
			}
		}

		else 
		{
			if (maxT > 0 && maxT < previousBestDistance)
			{
				intersect = Intersection(maxT, ray, this, maxTnormal);
				intersect.SetLocalIntersectingPoint((ray.getPoint(maxT) - minCorner).ToPoint());
			}

			else if (minT > 0 && minT < previousBestDistance)
			{
				intersect = Intersection(minT, ray, this, minTnormal);
				intersect.SetLocalIntersectingPoint((ray.getPoint(minT) - minCorner).ToPoint());
			}
		}

		return intersect;
	}

	float AABox::getArea() const
	{
		// Assuming that area cannot be negative:
		float length = maxCorner.x - minCorner.x;
		float width = maxCorner.y - minCorner.y;
		float height = maxCorner.z - minCorner.z;

		float xyPlaneArea = abs(length * width);
		float yzPlaneArea = abs(width * height);
		float zxPlaneArea = abs(length * height);

		return 2 * (xyPlaneArea + yzPlaneArea + zxPlaneArea);
	}
}
