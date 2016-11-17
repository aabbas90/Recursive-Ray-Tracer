#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

const int maxNumberElementsInLeaf = 1;
#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <rt/groups/Node.h>

namespace rt {
class MyComp
{
	private:
		int dimensionIndex;
	public:
		MyComp(int dimensionIndex);
		bool operator() (const Primitive *l, const Primitive *r);
		bool operator()(const Primitive* l, float valueToCompare);

};

class IntersectionElement
{
	bool operator<(const Node& l, const Node& r) 
	{
 		return l.nodeDistance < r.nodeDistance;
	}
private:
	Node* node;
	float nodeDistance;
}


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
	int getIndexFromPlaneLocation(int startindex, int endIncludingIndex, int dimensionIndex, float planeLocation);
	void buildBVH(Node* parentNode, int startIndex, int endIncludingIndex);
	void setBoundingBoxOfNode(Node *node, int startIndex, int endIncludingIndex);

private:
	Primitives unsortedList;
	Node* root;
};

}

#endif
