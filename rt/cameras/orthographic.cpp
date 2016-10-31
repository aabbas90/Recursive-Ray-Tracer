#include "orthographic.h"

namespace rt
{
	Ray OrthographicCamera::getPrimaryRay(float x, float y) const
	{
		Vector right = cross(up, forward);
		Vector upp = cross(forward, right); // Ensuring that all three vectors are perpendicular
		Point rayPoint = center + right * x * scaleX / 2 + upp * y * scaleY / 2;
		return Ray(rayPoint, forward.normalize());
	}
}