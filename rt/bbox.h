#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>


extern const float maxFloat;
extern const float minFloat;

namespace rt {

class Ray;

class BBox {
public:
    Point minCorner, maxCorner;

    BBox() {}
    BBox(const Point& min, const Point& max) : minCorner(min), maxCorner(max) {}
    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const { return maxCorner - minCorner; }

    std::pair<float,float> intersect(const Ray& ray) const;

    bool isUnbound();
};

}


#endif
