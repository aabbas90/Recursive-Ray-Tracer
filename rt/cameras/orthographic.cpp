#include "orthographic.h"

namespace rt
{
	OrthographicCamera::OrthographicCamera(
		const Point& center,
		const Vector& forward,
		const Vector& up,
		float scaleX,
		float scaleY
	) : center(center), forward(forward), up(up), scaleX(scaleX), scaleY(scaleY) {
		right = cross(up, forward);
		this->up = cross(forward, right); // Ensuring that all three vectors are perpendicular

	}

	Ray OrthographicCamera::getPrimaryRay(float x, float y) const
	{
		Point rayPoint = center + right * x * scaleX / 2 + up * y * scaleY / 2;
		return Ray(rayPoint, forward.normalize());
	}
}