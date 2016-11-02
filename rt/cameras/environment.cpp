#include "environment.h"
#include <math.h>
namespace rt
{
    EnvironmentCamera::EnvironmentCamera(
        const Point & center, 
        const Vector & forward, 
        const Vector & up, 
        float verticalOpeningAngle, 
        float horizonalOpeningAngle
        ) : center(center), forward(forward), up(up), verticalOpeningAngle(verticalOpeningAngle), horizonalOpeningAngle(horizonalOpeningAngle) {
        right = cross(up, forward).normalize();
        this->up = cross(forward, right).normalize(); // Ensuring that all three vectors are perpendicular
        this->forward = forward.normalize();
    }

    Ray EnvironmentCamera::getPrimaryRay(float x, float y) const
    {
        float phi =  x * verticalOpeningAngle / 2; 
        float theta = y * horizonalOpeningAngle / 2;

        //convert from spherical parametrization to cartesian coordinates
        float xx = cosf(phi) * cosf(theta);
        float yy = cosf(phi) * sinf(theta);
        float zz = sinf(phi);


        Vector direction = forward * zz + right * xx + up * yy;

        return Ray(center, direction.normalize());
    }
}
