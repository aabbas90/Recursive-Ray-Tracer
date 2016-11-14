#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>

namespace rt {

class BVH : public Group {
public:
	BVH();
	virtual BBox getBounds() const;
	virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual void rebuildIndex();
	virtual ~BVH();
	virtual void add(Primitive* p);
	virtual void setMaterial(Material* m);
	virtual void setCoordMapper(CoordMapper* cm);
};

}

#endif
