#include "ambient.h"

namespace rt {

AmbientLight::AmbientLight(const Float4& color) {
	this->intensity = color;
}


LightHit AmbientLight::getLightHit(const Point& p) const {
	LightHit result;
	result.direction = Vector (0, 0, 0);
	result.distance = 0;
	return result;
}

RGBColor AmbientLight::getIntensity(const LightHit& irr) const {
	return RGBColor(intensity.x, intensity.y, intensity.z);
}

}