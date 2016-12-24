#include <rt/coordmappers/tmapper.h>
#include <rt/intersection.h>

namespace rt
{
    TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
    {
		p0 = tv0;
		p1 = tv1;
		p2 = tv2;
    }
    TriangleMapper::TriangleMapper(Point ntv[3])
    {
		p0 = ntv[0];
		p1 = ntv[1];
		p2 = ntv[2];
    }

    Point TriangleMapper::getCoords(const Intersection& hit) const
    {
		Vector v1v2 = p1 - p0;
		Vector v1v3 = p2 - p0;
		Vector normalVector = cross(v1v2, v1v3);
		float fullArea = normalVector.length() / 2;

		Vector v3v2 = p2 - p1;
		Vector pv2 = hit.local() - p1;

		Vector v3v2pNormal = cross(v3v2, pv2);
		float u = (v3v2pNormal.length() / 2) / fullArea;

		Vector pv3 = hit.local() - p2;
		Vector v1v3pNormal = cross(pv3, v1v3);
		float v = (v1v3pNormal.length() / 2) / fullArea;
        return Point(u, v, 0);
    }
}