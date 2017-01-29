#ifndef CG1RAYTRACER_FOG_FOG_HEADER
#define CG1RAYTRACER_FOG_FOG_HEADER

#include <core/vector.h>

namespace rt {

class RGBColor;
class Point;


class Fog {
public:
	virtual float getAttenuation(float distance) const = 0;
    virtual RGBColor getIntensity(const Point &p) const = 0;
};

}

#endif
