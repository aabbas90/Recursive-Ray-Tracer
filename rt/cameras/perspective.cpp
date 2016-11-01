#include "perspective.h"
#include <math.h>
namespace rt
{
	PerspectiveCamera::PerspectiveCamera(
		const Point & center, 
		const Vector & forward, 
		const Vector & up, 
		float verticalOpeningAngle, 
		float horizonalOpeningAngle
		) : center(center), forward(forward), up(up), verticalOpeningAngle(verticalOpeningAngle), horizonalOpeningAngle(horizonalOpeningAngle)
	{
		this->right = cross(up, forward).normalize();
		this->up = cross(forward, right).normalize(); // Ensuring that all three vectors are perpendicular
	}

	Ray PerspectiveCamera::getPrimaryRay(float x, float y) const
	{
		Vector direction = forward.normalize() -
			(right * x * tan(horizonalOpeningAngle / 2.0f)) -
			(up * y * tan(verticalOpeningAngle / 2.0f));

		return Ray(center, direction.normalize());
	}
}
