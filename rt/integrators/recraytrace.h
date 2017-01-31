#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>
#include <core/vector.h>
#include <core/color.h>
#include <rt/intersection.h>
#include <rt/world.h>

namespace rt {

class World;
class Ray;
class RGBColor;

class RecursiveRayTracingIntegrator : public Integrator {
	const int maxRecursionDepth = 5;
public:
    RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray, int depth = 0) const;
};

}

#endif
