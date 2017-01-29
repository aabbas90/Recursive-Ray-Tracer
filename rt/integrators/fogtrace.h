#ifndef CG1RAYTRACER_INTEGRATORS_FOGTRACE_HEADER
#define CG1RAYTRACER_INTEGRATORS_FOGTRACE_HEADER

#include <rt/integrators/integrator.h>

namespace rt {

class World;
class Ray;
class RGBColor;

class RayFogTraceIntegrator : public Integrator {
public:
    RayFogTraceIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray, int depth = 0) const;
	RGBColor rayMarching (RGBColor &intensity, float distance, const Ray & ray, bool lightFlag) const;
};

}

#endif
