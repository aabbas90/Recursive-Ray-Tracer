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
		this->right = cross(forward, up).normalize();
		this->up = cross(right, forward).normalize(); // Ensuring that all three vectors are perpendicular
		spanningH = this->right * tan(horizonalOpeningAngle / 2.0f);
		spanningV = this->up  * tan(verticalOpeningAngle / 2.0f);
	}


	Ray PerspectiveCamera::getPrimaryRay(float x, float y) const
	{
		Vector direction = forward.normalize() + x * spanningH - y * spanningV;
		return Ray(center, direction.normalize());
	}
}
