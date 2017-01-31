#ifndef CG1RAYTRACER_LIGHTS_AREASPOTLIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_AREASPOTLIGHT_HEADER

#include <core/vector.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>

namespace rt {

	class AreaSpotLight : public Light {
	public:
		AreaSpotLight() {}
		AreaSpotLight(Solid* source, const Vector& direction, float angle, float exp, const RGBColor& intensity);
		virtual LightHit getLightHit(const Point& p) const;
		virtual RGBColor getIntensity(const LightHit& irr) const;
	private:
		Solid* source;
		Vector direction;
		float angle;
		float exp;
	};

}

#endif

