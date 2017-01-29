#ifndef CG1RAYTRACER_FOG_HOMOGENEOUS_HEADER
#define CG1RAYTRACER_FOG_HOMOGENEOUS_HEADER

#include <rt/fog/fog.h>
#include <core/color.h>
#include <core/point.h>


namespace rt {
class RGBColor;

class HomogeneousFog : public Fog {
private:
	RGBColor color;
	float density;
public:
	HomogeneousFog() {}
	HomogeneousFog(const RGBColor &color, float density);
	virtual float getAttenuation(float distance) const;
    virtual RGBColor getIntensity(const Point &p) const;
};


}
#endif 