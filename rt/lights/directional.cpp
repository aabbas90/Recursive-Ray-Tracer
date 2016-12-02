#include "directional.h"

namespace rt
{
	DirectionalLight::DirectionalLight(const Vector & direction, const RGBColor & color)
	{
	}
	LightHit DirectionalLight::getLightHit(const Point & p) const
	{
		return LightHit();
	}
	RGBColor DirectionalLight::getIntensity(const LightHit & irr) const
	{
		return RGBColor();
	}
}
