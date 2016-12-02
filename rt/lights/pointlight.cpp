#include "pointlight.h"
#include <rt/lights/light.h>

namespace rt
{
	PointLight::PointLight(const Point & position, const RGBColor & intensity)
	{
		this->intensity = intensity;
		this->position = position;
	}
	LightHit PointLight::getLightHit(const Point & p) const
	{
		LightHit hit;
		hit.direction = (position - p);
		hit.distance = hit.direction.length();
		hit.direction = hit.direction.normalize();
		return hit;
	}
	RGBColor PointLight::getIntensity(const LightHit & irr) const
	{
		float attenuation = 1 / (irr.distance * irr.distance);
		return RGBColor(intensity * attenuation);
	}
}
