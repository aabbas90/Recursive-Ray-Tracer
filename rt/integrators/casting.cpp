#include <rt/integrators/casting.h>
#include <core/vector.h>
#include <rt/intersection.h>

namespace rt
{
	RGBColor RayCastingIntegrator::getRadiance(const Ray& ray, int depth) const
	{
		Intersection intersection = this->world->scene->intersect(ray, MAX_DIST);
		float grayColor = 0;
		
		if (intersection)
			grayColor = std::abs(dot(intersection.normal(), ray.d));

		return RGBColor(grayColor, grayColor, grayColor);
	}
}