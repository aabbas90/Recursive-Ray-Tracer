#include <rt/groups/simplegroup.h>
#include <core/assert.h>

using namespace rt;

Intersection SimpleGroup::intersect(const Ray& ray, float previousBestDistance) const
{
    Intersection intersection, smallestIntersection;
    for(auto &primitive : primitives) 
    {
        intersection = primitive->intersect(ray, previousBestDistance);
        if(intersection && (intersection.distance < previousBestDistance))
        {
            smallestIntersection = intersection;
            previousBestDistance = intersection.distance;
        }
    }
    return smallestIntersection;
}
void SimpleGroup::rebuildIndex()
{
    NOT_IMPLEMENTED;
}
void SimpleGroup::add(Primitive* p)
{
    primitives.push_back(p);
}
void SimpleGroup::setMaterial(Material* m) 
{
    NOT_IMPLEMENTED;
}
void SimpleGroup::setCoordMapper(CoordMapper* cm)
{
    NOT_IMPLEMENTED;
}