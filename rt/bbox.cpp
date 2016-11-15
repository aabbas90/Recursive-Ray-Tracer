#include <rt/bbox.h>
#include <core/assert.h>
#include <rt/ray.h>
#include <core/point.h>
#include <algorithm>

const float maxFloat = std::numeric_limits<float>::max();
const float minFloat = std::numeric_limits<float>::min();

namespace rt
{
	// BBox(const BBox &bbox)
	// {

	// }
	BBox BBox::empty()
	{
		return BBox::BBox(Point(0, 0, 0), Point(0, 0, 0));
	}
	BBox BBox::full()
	{
		return BBox::BBox(Point(minFloat, minFloat, minFloat), Point(maxFloat, maxFloat, maxFloat));
	}
	void BBox::extend(const Point & point)
	{
		minCorner = min(this->minCorner, point);
		maxCorner = max(this->maxCorner, point);
	}
	void BBox::extend(const BBox & bbox)
	{
		this->maxCorner = max(this->maxCorner, bbox.maxCorner);
		this->minCorner = min(this->minCorner, bbox.minCorner);
	}
	std::pair<float, float> BBox::intersect(const Ray & ray) const
	{
		// Return no intersection if empty:
		if ((maxCorner - minCorner).lensqr() == 0)
			return std::pair<float, float>(maxFloat, minFloat);

		// Return successful intersection if full:
		if (minCorner == Point(minFloat, minFloat, minFloat) && 
			maxCorner == Point(maxFloat, maxFloat, maxFloat))
			return std::pair<float, float>(minFloat, maxFloat);

		float minT, maxT;

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

		float tyMin = std::min(ty0, ty1);
		float tyMax = std::max(ty0, ty1);

		// Are these the two t0's and t1's required? Because there are two more of them as well.
		if ((minT > tyMax) || (tyMin > maxT))
			return std::pair<float, float>(tyMin, maxT);

		if (tyMin > minT)
		{
			minT = tyMin;
		}

		if (tyMax < maxT)
		{
			maxT = tyMax;
		}

		float tz0 = (minCorner.z - ray.o.z) / ray.d.z;
		float tz1 = (maxCorner.z - ray.o.z) / ray.d.z;

		float tzMin = std::min(tz0, tz1);
		float tzMax = std::max(tz0, tz1);

		// Are these the two t0's and t1's required? Because there are two more of them as well.
		if ((minT > tzMax) || (tzMin > maxT))
			return std::pair<float, float>(tzMin, maxT);

		if (tzMin > minT)
		{
			minT = tzMin;
		}

		if (tzMax < maxT)
		{
			maxT = tzMax;
		}

		return std::pair<float, float>(minT, maxT);
	}

	bool BBox::isUnbound()
	{
		if (minCorner.x == minFloat || minCorner.y == minFloat || minCorner.z == minFloat ||
			maxCorner.x == maxFloat || maxCorner.y == maxFloat || maxCorner.z == maxFloat)
			return 1;

		return 0;
	}
}