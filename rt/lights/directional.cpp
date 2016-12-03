#include "directional.h"

namespace rt
{
	DirectionalLight::DirectionalLight(const Vector & direction, const RGBColor & color)
	{
		intensity = color;
		this->direction = -direction;
	}

	LightHit DirectionalLight::getLightHit(const Point & p) const
	{
		LightHit hit;
		hit.direction = direction;
		hit.distance = FLT_MAX;
		hit.direction = hit.direction.normalize();
		return hit;
	}

	RGBColor DirectionalLight::getIntensity(const LightHit & irr) const
	{
		return intensity;
	}
}
