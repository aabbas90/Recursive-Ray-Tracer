#ifndef CG1RAYTRACER_INTEGRATORS_INTEGRATOR_HEADER
#define CG1RAYTRACER_INTEGRATORS_INTEGRATOR_HEADER

namespace rt {

class World;
class Ray;
class RGBColor;
const float MAX_DIST = 10000000;
const float displacement = 0.0001f;

class Integrator {
public:
	Integrator() {}
	Integrator(World* world) : world(world) {}
	virtual RGBColor getRadiance(const Ray& ray, int depth = 0) const = 0;
protected:
	World* world;
};

}

#endif
