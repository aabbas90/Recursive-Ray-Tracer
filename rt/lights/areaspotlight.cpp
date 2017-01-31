#include "areaspotlight.h"

namespace rt
{
	AreaSpotLight::AreaSpotLight(Solid * source, const Vector & direction, float angle, float exp, const RGBColor & intensity)
	{
		this->source = source;
		this->direction = direction;
		this->angle = angle;
		this->exp = exp;
		this->intensity = intensity;
	}

	LightHit AreaSpotLight::getLightHit(const Point & p) const
	{
		LightHit hit;
		Point position = source->sample();
		hit.direction = (position - p);
		hit.distance = hit.direction.length();
		hit.direction = hit.direction.normalize();
		return hit;
	}

	RGBColor AreaSpotLight::getIntensity(const LightHit & irr) const
	{
		float attenuation = 1 / (irr.distance * irr.distance);

		float currentAngle = acos(dot(irr.direction.normalize(), -direction.normalize()));
		if (currentAngle > angle || currentAngle < 0)
			return RGBColor(0, 0, 0);

		return intensity * powf(cos(currentAngle), exp) * attenuation * source->getArea() * source->material->getEmission(source->sample(), Vector(0.0f, 0.0f, 0.0f), irr.direction);
	}
}
