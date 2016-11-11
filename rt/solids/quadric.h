#ifndef CG1RAYTRACER_SOLIDS_QUADRIC_HEADER
#define CG1RAYTRACER_SOLIDS_QUADRIC_HEADER

#include <rt/solids/solid.h>
#include <rt/bbox.h>
#include <rt/intersection.h>

namespace rt {

class Quadric : public Solid {
public:
	Quadric() {}
	Quadric(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i, const float j, CoordMapper* texMapper, Material* material);
	virtual BBox getBounds() const;
	virtual Intersection intersect(const Ray& ray, float previousBestDistance) const;
	virtual Point sample() const;
	virtual float getArea() const;

private:
	float a, b, c, d, e, f, g, h, i, j;
	
};

}

#endif
