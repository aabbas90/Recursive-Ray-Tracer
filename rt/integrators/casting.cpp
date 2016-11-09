#include <rt/integrators/casting.h>
#include <core/vector.h>
#include <rt/intersection.h>

using namespace rt;

float MAX_DIST = 10000000;

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const
{    
    Intersection intersection = this->world->scene->intersect(ray, MAX_DIST);
    float grayColor = dot(intersection.normal(), ray.d);
    return RGBColor(grayColor, grayColor, grayColor);
}