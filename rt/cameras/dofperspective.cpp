#include <rt/cameras/dofperspective.h>
#include <math.h>
#include <core/random.h>
#include <core/scalar.h>

namespace rt
{
    DOFPerspectiveCamera::DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
    ) : center(center), forward(forward), up(up), verticalOpeningAngle(verticalOpeningAngle), horizonalOpeningAngle(horizonalOpeningAngle), focalDistance(focalDistance), apertureRadius(apertureRadius)
    {
		this->right = cross(forward, up).normalize();
		this->up = cross(forward, right).normalize(); // Ensuring that all three vectors are perpendicular
		spanningH = this->right * tan(horizonalOpeningAngle / 2.0f);
		spanningV = this->up  * tan(verticalOpeningAngle / 2.0f);
    }

    Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const
    {
		Vector direction = forward.normalize() + x * spanningH + y * spanningV;
        Point focalPoint = Ray(center,direction.normalize()).getPoint(focalDistance); //h
        //get some vector randomly in a circle of radius apertureRadius
        
        float theta = random() * 2 * pi; //random theta btw [0,2pi]
        float r = random() * apertureRadius * 0.5f;
		float x_polar = std::cos(theta) * r;
		float y_polar = std::sin(theta) * r;

        Point shiftedCenter = center + x_polar * spanningH.normalize() + y_polar * spanningV.normalize();
        Vector shiftedDirection = focalPoint - shiftedCenter;
        return Ray(shiftedCenter, shiftedDirection.normalize());
    }

}