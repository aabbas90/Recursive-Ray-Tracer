#include <rt/lights/arealight.h>

namespace rt
{
	AreaLight::AreaLight(Solid* source)
	{
        	this->source = source;
	}

	LightHit AreaLight::getLightHit(const Point & p) const
	{
		LightHit hit;
       	Point position = source->sample();
		hit.direction = (position - p);
		hit.distance = hit.direction.length();
		hit.direction = hit.direction.normalize();
		return hit;
	}

	RGBColor AreaLight::getIntensity(const LightHit & irr) const
	{
        //dummy value TODO
        return RGBColor::white();
	}
}
