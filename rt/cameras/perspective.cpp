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
		) : center(center), forward(forward), up(up), verticalOpeningAngle(verticalOpeningAngle), horizonalOpeningAngle(horizonalOpeningAngle) {
		right = cross(up, forward);
		this->up = cross(forward, right); // Ensuring that all three vectors are perpendicular
	}

	Ray PerspectiveCamera::getPrimaryRay(float x, float y) const
	{

		Point rayPoint = center + right * x * tan(horizonalOpeningAngle / 2)  + up * y * tan(verticalOpeningAngle /2);
		//Vector direction = right * x * tan(horizonalOpeningAngle / 2)  + upp * y * tan(verticalOpeningAngle /2);
		return Ray(rayPoint, forward.normalize());
	}
}
