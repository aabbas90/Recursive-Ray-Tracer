#include "ray.h"

namespace rt
{
	Ray::Ray(const Point & o, const Vector & d) : o(o), d(d) {
	}

	Point Ray::getPoint(float distance) const {
		//TODO: Check if right logic
		return o + distance * d;
	}
}
