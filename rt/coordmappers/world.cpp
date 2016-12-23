#include <rt/coordmappers/world.h>

namespace rt
{
    WorldMapper::WorldMapper()
    {
        scale = Float4(1.0f, 1.0f, 1.0f, 1.0f); //point
    }
    WorldMapper::WorldMapper(const Float4& scale)
    :scale(scale){}
    Point WorldMapper::getCoords(const Intersection& hit) const
    {
        Point hitPoint = hit.hitPoint();
        return Point(scale.x * hitPoint.x, scale.y * hitPoint.y, scale.z * hitPoint.z);
    }
}
