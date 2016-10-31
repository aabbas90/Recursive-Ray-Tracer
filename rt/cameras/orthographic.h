#ifndef CG1RAYTRACER_CAMERAS_ORTHOGRAPHIC_HEADER
#define CG1RAYTRACER_CAMERAS_ORTHOGRAPHIC_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>

namespace rt {

class OrthographicCamera : public Camera {
private:
	Point center;
	Vector forward;
	Vector up;
	Vector right;
	float scaleX, scaleY;

public:
	OrthographicCamera(
		const Point& center,
		const Vector& forward,
		const Vector& up,
		float scaleX,
		float scaleY
	); 

    Ray getPrimaryRay(float x, float y) const;
};

}


#endif
