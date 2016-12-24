#include <rt/coordmappers/tmapper.h>
#include <rt/intersection.h>

namespace rt
{
    TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
    {
        
    }
    TriangleMapper::TriangleMapper(Point ntv[3])
    {

    }
    Point TriangleMapper::getCoords(const Intersection& hit) const
    {
        return Point();
    }
}