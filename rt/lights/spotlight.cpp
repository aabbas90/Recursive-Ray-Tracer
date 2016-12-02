#include "spotlight.h"

namespace rt
{
	SpotLight::SpotLight(const Point & position, const Vector & direction, float angle, float exp, const RGBColor & intensity)
	{
	}
	LightHit SpotLight::getLightHit(const Point & p) const
	{
		return LightHit();
	}
	RGBColor SpotLight::getIntensity(const LightHit & irr) const
	{
		return RGBColor();
	}
}
