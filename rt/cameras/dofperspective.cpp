#include <rt/cameras/dofperspective.h>
#include <math.h>
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
        this->right = cross(up, forward).normalize();
		this->up = cross(forward, right).normalize(); 
    }

    Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const
    {
        //DUMMY
        return Ray(center, forward);
    }

}