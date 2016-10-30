#include "orthographic.h"

namespace rt
{
	OrthographicCamera::OrthographicCamera(const Point & center, const Vector & forward, const Vector & up, float scaleX, float scaleY)
	{
	}

	Ray OrthographicCamera::getPrimaryRay(float x, float y) const
	{
		return Ray();
	}
}