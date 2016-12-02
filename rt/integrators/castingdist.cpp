#include "castingdist.h"
#include <core/vector.h>
#include <rt/intersection.h>

namespace rt
{
	RayCastingDistIntegrator::RayCastingDistIntegrator(World * world, const RGBColor & nearColor, float nearDist, const RGBColor & farColor, float farDist)
	{
		this->world = world;
		this->nearColor = nearColor;
		this->nearDist = nearDist;
		this->farColor = farColor;
		this->farDist = farDist;
	}

	RGBColor RayCastingDistIntegrator::getRadiance(const Ray & ray) const
	{
		Intersection intersection = this->world->scene->intersect(ray, MAX_DIST);
		RGBColor colorValue = RGBColor(0, 0, 0);
		if (intersection)
		{
			colorValue = (intersection.distance - nearDist) * farColor / (farDist - nearDist) + (farDist - intersection.distance) * nearColor / (farDist - nearDist);
			colorValue = colorValue * std::abs(dot(intersection.normal(), ray.d));
		}
		return colorValue;
	}
}
