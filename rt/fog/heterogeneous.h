#ifndef CG1RAYTRACER_FOG_HETEROGENEOUS_HEADER
#define CG1RAYTRACER_FOG_HETEROGENEOUS_HEADER

#include <rt/fog/fog.h>
#include <core/color.h>
#include <core/point.h>
#include <rt\textures\perlin.h>


namespace rt {
class RGBColor;
class PerlinTexture;

class HeterogeneousFog : public Fog {
private:
	PerlinTexture *pTexture;
	float density;
public:
	HeterogeneousFog() {}
	HeterogeneousFog(PerlinTexture *p, float density);
	virtual float getAttenuation(float distance) const;
    virtual RGBColor getIntensity(const Point &p) const;
};


}
#endif 