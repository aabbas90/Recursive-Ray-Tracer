#ifndef CG1RAYTRACER_WORLD_HEADER
#define CG1RAYTRACER_WORLD_HEADER

#include <rt/primitive.h>
namespace rt {
class Light;
class Fog;
class World {
public:
    Primitive* scene;
	typedef std::vector<Light*> LightVector;
    LightVector light;
	Fog *fog;

};
}

#endif
