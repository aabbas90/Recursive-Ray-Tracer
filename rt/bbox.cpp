#include <rt/bbox.h>
#include <core/assert.h>

float maxFloat = std::numeric_limits<float>::max();

namespace rt
{
	// BBox(const BBox &bbox)
	// {

	// }
	BBox BBox::empty()
	{
		return BBox::BBox(0.0, 0.0);
	}
	BBox BBox::full()
	{
		return BBox::BBox(maxFloat, maxFloat);
	}
	void BBox::extend(const Point & point)
	{
		return BBox::BBox(min(min(this->min, point), this->max), max(max(this->min, point), this->max));
	}
	void BBox::extend(const BBox & bbox)
	{
		this->max = max(this->max, bbox.max); 
		this->min = min(this->min, bbox.min);
	}
	std::pair<float, float> BBox::intersect(const Ray & ray) const
	{
		NOT_IMPLEMENTED;
	}
	bool BBox::isUnbound()
	{
		NOT_IMPLEMENTED;
	}
}