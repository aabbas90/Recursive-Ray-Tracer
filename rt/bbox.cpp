#include <rt/bbox.h>
#include <core/assert.h>

float maxFloat = std::numeric_limits<float>::max();
float minFloat = std::numeric_limits<float>::min();

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
		NOT_IMPLEMENTED;
	}
	bool BBox::isUnbound()
	{
		if (minCorner.x == minFloat || minCorner.y == minFloat || minCorner.z == minFloat ||
			maxCorner.x == maxFloat || maxCorner.y == maxFloat || maxCorner.z == maxFloat)
			return 1;

		return 0;
	}
}