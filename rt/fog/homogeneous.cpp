#include "homogeneous.h"
#include <core\scalar.h>

namespace rt {

HomogeneousFog::HomogeneousFog(const RGBColor &color, float density) {
	this->color = color;
	this->density = density;
}

float HomogeneousFog::getAttenuation(float distance) const {
	return exp(-density * distance);
}

RGBColor HomogeneousFog::getIntensity(const Point &p) const {
	return color;
}

}