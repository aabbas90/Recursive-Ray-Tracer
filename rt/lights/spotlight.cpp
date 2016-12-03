#include "spotlight.h"

namespace rt
{
	SpotLight::SpotLight(const Point & position, const Vector & direction, float angle, float exp, const RGBColor & intensity)
	{
		this->position = position;
		this->direction = direction;
		this->angle = angle;
		this->exp = exp;
		this->intensity = intensity;
	}
	LightHit SpotLight::getLightHit(const Point & p) const
	{
		LightHit hit;
		hit.direction = (position - p);
		hit.distance = hit.direction.length();
		hit.direction = hit.direction.normalize();
		return hit;
	}
	RGBColor SpotLight::getIntensity(const LightHit & irr) const
	{
		float attenuation = 1 / (irr.distance * irr.distance);

		float currentAngle = acos(dot(irr.direction.normalize(), -direction.normalize()));
		if (currentAngle > angle || currentAngle < 0)
			return RGBColor(0, 0, 0);

		return intensity * powf(cos(currentAngle), exp) * attenuation;
	}
}
