#include <rt/coordmappers/plane.h>

namespace rt
{
    PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2)
    :e1(e1), e2(e2)
    {
        Vector normal = cross(e1, e2).normalize();
        
    }
    Point PlaneCoordMapper::getCoords(const Intersection& hit) const 
    {

    } 
}
