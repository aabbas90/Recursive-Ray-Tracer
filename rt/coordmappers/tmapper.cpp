#include <rt/coordmappers/tmapper.h>
#include <rt/intersection.h>
#include <core/interpolate.h>
namespace rt
{
    TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
    : tv0(tv0), tv1(tv1), tv2(tv2){} 
    TriangleMapper::TriangleMapper(Point ntv[3])
    : tv0(ntv[0]), tv1(ntv[1]), tv2(ntv[2]){}
    Point TriangleMapper::getCoords(const Intersection& hit) const
    {
        Point hitPoint = hit.local();
        // return Point (tv0 * hitPoint.z + tv1 * hitPoint.x + tv2 * hitPoint.y);
        return lerpbar(tv0, tv1, tv2, hitPoint.x, hitPoint.z);
    }
}