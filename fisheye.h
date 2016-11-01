
#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>

namespace rt {

	class FishEyeCamera : public Camera {
	private:
		Point center;
		Vector forward;
		Vector up;
		Vector right;

	public:
		FishEyeCamera(
			const Point& center,
			const Vector& forward,
			const Vector& up
		);

		Ray getPrimaryRay(float x, float y) const;
	};

}