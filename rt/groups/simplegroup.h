#ifndef CG1RAYTRACER_GROUPS_SIMPLEGROUP_HEADER
#define CG1RAYTRACER_GROUPS_SIMPLEGROUP_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/intersection.h>

namespace rt {
class BBox;

class SimpleGroup : public Group {
public:
    virtual BBox getBounds() const = 0;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
    virtual void add(Primitive* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
private:
    Primitives primitives;
};


}

#endif
