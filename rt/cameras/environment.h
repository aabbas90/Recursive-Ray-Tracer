#ifndef CG1RAYTRACER_CAMERAS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_CAMERAS_ENVIRONMENT_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>

namespace rt {

class EnvironmentCamera : public Camera {
private:
	Point center;
	Vector forward;
	Vector up;
	Vector right;
	float verticalOpeningAngle, horizonalOpeningAngle;
public:
    EnvironmentCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle
        );

    virtual Ray getPrimaryRay(float x, float y) const;
};

}


#endif
