#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

const int maxNumberElementsInLeaf = 5;
#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <rt/groups/Node.h>
#include <queue>

namespace rt {
class PrimitiveComparator
{
	private:
		int dimensionIndex;
	public:
		PrimitiveComparator(int dimensionIndex);
		bool operator() (const Primitive *l, const Primitive *r) const;
		bool operator() (const Primitive* l, float valueToCompare) const;

};

class IntersectionElement
{
public:
	BVHNode* node;
	float nodeDistance;
	bool isIntersected = false;
	IntersectionElement() {}
	IntersectionElement(BVHNode * node, float nodeDistance, bool isIntersected)
		:node(node), nodeDistance(nodeDistance), isIntersected(isIntersected) {}
	bool operator < (const IntersectionElement& r) const
	{
		return this->nodeDistance > r.nodeDistance;
	}

	bool operator() (const IntersectionElement& l, const IntersectionElement& r) const
	{
		return l.nodeDistance > r.nodeDistance;
	}
};


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
	int getIndexFromPlaneLocation(unsigned int startindex, unsigned int endIncludingIndex, int dimensionIndex, float planeLocation);
	void buildBVH(BVHNode* parentNode, unsigned int startIndex, unsigned int endIncludingIndex);
	void setBoundingBoxOfNode(BVHNode *node, unsigned int startIndex, unsigned int endIncludingIndex);
	Intersection IterateOverQueue(std::priority_queue<IntersectionElement> pqueue, const Ray & ray, float previousBestDistance) const;

private:
	Primitives unsortedList;
	BVHNode* root;
};

}

#endif
