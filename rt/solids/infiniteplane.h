#ifndef CG1RAYTRACER_SOLIDS_INFINITEPLANE_HEADER
#define CG1RAYTRACER_SOLIDS_INFINITEPLANE_HEADER

#include <rt/solids/solid.h>
#include <core/float4.h>
#include <rt/intersection.h>
#include <rt/solids/quadric.h>

namespace rt {

class InfinitePlane : public Solid {
public:
	InfinitePlane() {}
	InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material);

	virtual BBox getBounds() const;
	virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
	virtual float getArea() const;
	Quadric* ToQuadric();

private:
	Point origin;
	Vector normal;
};

}


#endif
