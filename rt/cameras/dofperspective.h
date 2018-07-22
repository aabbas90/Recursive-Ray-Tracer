#ifndef CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>

namespace rt {

class DOFPerspectiveCamera : public Camera {
    private:
	Point center;
	Vector forward;
	Vector up;
	Vector right;
    Vector spanningH, spanningV;
	float verticalOpeningAngle, horizonalOpeningAngle;
    float focalDistance, apertureRadius;

public:
    DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
        );

    virtual Ray getPrimaryRay(float x, float y) const;

};

}


#endif
