#include "recraytrace.h"
#include <core/color.h>
#include <core/vector.h>
#include <rt/lights/light.h>
#include <rt/intersection.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt
{
	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray & ray, int depth) const
	{
		RGBColor color = RGBColor(0, 0, 0);
		if (depth >= maxRecursionDepth)
			return color;

		Intersection intersection = this->world->scene->intersect(ray, MAX_DIST);

		if (intersection)
		{
			Vector normal = intersection.normal().normalize();
			if (dot(normal, ray.d.normalize()) > 0)
				normal = -1.0f * normal;

			auto currentMaterial = intersection.solid->material;
			auto outDir = ray.d.normalize();

			if (currentMaterial->useSampling() == Material::Sampling::SAMPLING_NOT_NEEDED)
			{
				for (auto lightSource : this->world->light)
				{
					LightHit lightHit = lightSource->getLightHit(intersection.hitPoint());
					Vector inDir = lightHit.direction;
					if (dot(inDir, normal) < 0)
						continue;

					Ray shadowRay = Ray(intersection.hitPoint() + displacement * inDir, inDir);
					Intersection shadowRayIntersection = this->world->scene->intersect(shadowRay, lightHit.distance);
					if (shadowRayIntersection)
						continue;

					RGBColor reflected = currentMaterial->getReflectance(intersection.local(), normal, outDir, inDir);
					color = color + reflected * lightSource->getIntensity(lightHit);
				}
			}

			else if (currentMaterial->useSampling() == Material::Sampling::SAMPLING_ALL)
			{
				auto reflectance = currentMaterial->getSampleReflectance(intersection.local(), normal, outDir);
				Vector inDir = reflectance.direction.normalize();
				Ray shadowRay = Ray(intersection.hitPoint() + displacement * inDir, inDir);

				RGBColor incomingLightColor = this->getRadiance(shadowRay, depth + 1);
				color = incomingLightColor * reflectance.reflectance;
			}
		}

		return color.clamp();
	}
}
