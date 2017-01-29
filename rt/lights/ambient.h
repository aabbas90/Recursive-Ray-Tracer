#ifndef CG1RAYTRACER_LIGHTS_AMBIENT_HEADER
#define CG1RAYTRACER_LIGHTS_AMBIENT_HEADER

#include <rt/lights/light.h>
#include <core/color.h>
#include <core\vector.h>
#include <core\float4.h>

namespace rt {

class AmbientLight : public Light {
public:
	Float4 intensity;
	AmbientLight() {}
	AmbientLight(const Float4& color);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif

