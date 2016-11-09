#include <rt/integrators/casting.h>
#include <core/vector.h>
#include <rt/intersection.h>

namespace rt
{
	float MAX_DIST = 10000000;

	RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const
	{
		Intersection intersection = this->world->scene->intersect(ray, MAX_DIST);
		float grayColor = 0;
		
		if (intersection)
			grayColor = abs(dot(intersection.normal(), ray.d));

		return RGBColor(grayColor, grayColor, grayColor);
	}
}