#include "heterogeneous.h"
#include <core\scalar.h>

namespace rt {

HeterogeneousFog::HeterogeneousFog(PerlinTexture *pTexture, float density) {
	this->pTexture = pTexture;
	this->density = density;
}

float HeterogeneousFog::getAttenuation(float distance) const {
	return exp(-density * distance);
}

RGBColor HeterogeneousFog::getIntensity(const Point &p) const {
	return pTexture->getColor(p);
}

}