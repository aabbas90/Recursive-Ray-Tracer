#ifndef CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER
#define CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER

#include <rt/integrators/integrator.h>
#include <core/color.h>
#include <rt/world.h>


namespace rt {

class World;
class Ray;
class RGBColor;

class RayCastingDistIntegrator : public Integrator {
public:
    RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist);
    virtual RGBColor getRadiance(const Ray& ray, int depth = 0) const;
private:
    RGBColor nearColor, farColor;
    float nearDist, farDist;
};

}

#endif
