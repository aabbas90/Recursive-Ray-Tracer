#include "raytrace.h"
#include <core/vector.h>
#include <rt/lights/light.h>
#include <rt/intersection.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt
{
	RGBColor RayTracingIntegrator::getRadiance(const Ray & ray, int depth) const
	{
		Intersection intersection = this->world->scene->intersect(ray, MAX_DIST);
		RGBColor color = RGBColor(0, 0, 0);
		if (intersection)
		{
			Vector normal = intersection.normal().normalize();
			if (dot(normal, ray.d.normalize()) > 0)
				normal = -1.0f * normal;

			auto solid = intersection.solid;
			
			for (auto lightSource : this->world->light)
			{
				LightHit lightHit = lightSource->getLightHit(intersection.hitPoint());

				if (dot(lightHit.direction, normal) < 0)
					continue;

				Ray shadowRay = Ray(intersection.hitPoint() + displacement * lightHit.direction, lightHit.direction);
				Intersection shadowRayIntersection = this->world->scene->intersect(shadowRay, lightHit.distance);
				if (shadowRayIntersection)
					continue;

				RGBColor reflected = solid->material->getReflectance(intersection.local(), normal, ray.d.normalize(), lightHit.direction);
				color = color + reflected * lightSource->getIntensity(lightHit);
			}

		}

		return color.clamp();
	}
}
