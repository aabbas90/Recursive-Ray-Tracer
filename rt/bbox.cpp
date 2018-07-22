#include <rt/bbox.h>
#include <core/assert.h>
#include <rt/ray.h>
#include <core/point.h>
#include <algorithm>
<<<<<<< HEAD
#include <tuple>
=======
#include<tuple>
#include <math.h>

>>>>>>> chitra

const float maxFloat = std::numeric_limits<float>::max();
const float minFloat = -std::numeric_limits<float>::max();

namespace rt
{
	// BBox(const BBox &bbox)
	// {

	// }
	BBox BBox::empty()
	{
		return BBox::BBox();
	}
	BBox BBox::full()
	{
		return BBox::BBox(Point(minFloat, minFloat, minFloat), Point(maxFloat, maxFloat, maxFloat));
	}
	void BBox::extend(const Point & point)
	{
		if (this->isEmpty)
		{
			minCorner = point;
			maxCorner = point;
		}
		else
		{
			minCorner = min(this->minCorner, point);
			maxCorner = max(this->maxCorner, point);
		}
		this->isEmpty = false;
	}
	void BBox::extend(const BBox & bbox)
	{
		if (bbox.isEmpty)
			return;

		if (this->isEmpty)
		{
			this->minCorner = bbox.minCorner;
			this->maxCorner = bbox.maxCorner;
		}

		else
		{
			this->maxCorner = max(this->maxCorner, bbox.maxCorner);
			this->minCorner = min(this->minCorner, bbox.minCorner);
		}
		this->isEmpty = false;
	}
<<<<<<< HEAD

	void BBox::Inflate(float factor)
	{
		float width = maxCorner.x - minCorner.x;
		float length = maxCorner.y - minCorner.y;
		float height = maxCorner.z - minCorner.z;
		Vector inflationVector = Vector(0, 0, 0);
		if (width < length)
		{
			if (width < height)
			{
				inflationVector = Vector(factor, 0, 0);
			}
			else
			{
				inflationVector = Vector(0, 0, factor);
			}
		}
		else
		{
			if (length < height)
			{
				inflationVector = Vector(0, factor, 0);
			}
			else
			{
				inflationVector = Vector(0, 0, factor);
			}
		}
		this->minCorner = this->minCorner - inflationVector;
		this->maxCorner = this->maxCorner + inflationVector;
	}

=======
>>>>>>> chitra
	std::tuple< float, float, bool> BBox::intersect(const Ray & ray) const
	{
		// Return no intersection if empty:
		if ((maxCorner - minCorner).lensqr() == 0 || this->isEmpty)
			return std::tuple< float, float, bool>( maxFloat, minFloat, false);

		// Return successful intersection if full:
		if (minCorner == Point(minFloat, minFloat, minFloat) && 
			maxCorner == Point(maxFloat, maxFloat, maxFloat))
			return std::tuple<float, float, bool>(minFloat, maxFloat, true);

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
<<<<<<< HEAD
		if ((minT > tyMax + 0.5) || (tyMin > maxT + 0.5))
=======
		if ((minT > tyMax) || (tyMin > maxT))
>>>>>>> chitra
			return std::tuple<float, float, bool>( tyMin, maxT, false);

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
<<<<<<< HEAD
		if ((minT > tzMax + 0.5) || (tzMin > maxT + 0.5))
=======
		if ((minT > tzMax) || (tzMin > maxT))
>>>>>>> chitra
			return std::tuple<float, float, bool>(tzMin, maxT, false);

		if (tzMin > minT)
		{
			minT = tzMin;
		}

		if (tzMax < maxT)
		{
			maxT = tzMax;
		}

		if (minT < 0 && maxT < 0)
			return std::tuple<float, float, bool>(minT, maxT, false);

<<<<<<< HEAD
		if (minT < 0)
			minT = maxT;

		return std::tuple<float, float, bool>(minT, maxT, true);
=======
		// TO DO: What to do when the ray origin is inside the box? then one intersection is -ive and one +ive
		// if (minT < 0)
		//	minT = maxT;

		return std::tuple<float, float, bool>(minT, maxT, true);
	}


	void BBox::Inflate(float factor)
	{
		float width = maxCorner.x - minCorner.x;
		float length = maxCorner.y - minCorner.y;
		float height = maxCorner.z - minCorner.z;
		Vector inflationVector = Vector(0, 0, 0);
		if (width < length)
		{
			if (width < height)
			{
				inflationVector = Vector(factor, 0, 0);
			}
			else
			{
				inflationVector = Vector(0, 0, factor);
			}
		}
		else
		{
			if (length < height)
			{
				inflationVector = Vector(0, factor, 0);
			}
			else
			{
				inflationVector = Vector(0, 0, factor);
			}
		}
		this->minCorner = this->minCorner - inflationVector;
		this->maxCorner = this->maxCorner + inflationVector;
>>>>>>> chitra
	}

	bool BBox::isUnbound()
	{
		if (minCorner.x == minFloat || minCorner.y == minFloat || minCorner.z == minFloat ||
			maxCorner.x == maxFloat || maxCorner.y == maxFloat || maxCorner.z == maxFloat)
			return 1;

		return 0;
	}

	bool BBox::isInside(BBox& parent, BBox& child)
	{
		BBox parentBox = BBox(parent.minCorner, parent.maxCorner);
		parentBox.extend(child);
		if (parentBox.minCorner == parent.minCorner && parentBox.maxCorner == parent.maxCorner)
			return true;
		else
			return false;
	}

	std::pair<int, float> BBox::findGreatestDimensionAndMiddleLocation()
	{
		float xLength = maxCorner.x - minCorner.x;
		float yLength = maxCorner.y - minCorner.y;
		float zLength = maxCorner.z - minCorner.z;
		if (xLength > yLength)
		{
			if (xLength > zLength)
				return std::pair<int, float>(0, xLength / 2 + minCorner.x);

			else
				return std::pair<int, float>(2, zLength / 2 + minCorner.z);
		}

		else
		{
			if (yLength > zLength)
				return std::pair<int, float>(1, yLength / 2 + minCorner.y);
			else
				return std::pair<int, float>(2, zLength / 2 + minCorner.z);
		}

		return std::pair<int, float>();
	}

	float BBox::getSurfaceArea()
	{
		float length = maxCorner.x - minCorner.x;
		float width = maxCorner.y - minCorner.y;
		float height = maxCorner.z - minCorner.z;

		float xyPlaneArea = fabs(length * width);
		float yzPlaneArea = fabs(width * height);
		float zxPlaneArea = fabs(length * height);

		return 2 * (xyPlaneArea + yzPlaneArea + zxPlaneArea);
	}
	float BBox::getXLength()
	{
		if (isEmpty)
			return 0;

		return this->maxCorner.x - this->minCorner.x;
	}

	float BBox::getYLength()
	{
		if (isEmpty)
			return 0;

		return this->maxCorner.y - this->minCorner.y;
	}

	float BBox::getZLength()
	{
		if (isEmpty)
			return 0;

		return this->maxCorner.z - this->minCorner.z;
	}
}