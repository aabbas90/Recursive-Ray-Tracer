#include "perspective.h"

namespace rt
{
	PerspectiveCamera::PerspectiveCamera(const Point & center, const Vector & forward, const Vector & up, float verticalOpeningAngle, float horizonalOpeningAngle)
	{
	}

	Ray PerspectiveCamera::getPrimaryRay(float x, float y) const
	{
		return Ray();
	}
}
