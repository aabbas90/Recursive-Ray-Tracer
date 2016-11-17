#ifndef CG1RAYTRACER_GROUPS_NODE_HEADER
#define CG1RAYTRACER_GROUPS_NODE_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#define maxNumberOfChildren 3;
namespace rt
{
	class BVHNode
	{

	public:
		BVHNode();
		BBox boundingBox;
		void extendBox(const BBox& inputBox);
		BVHNode* leftChild = nullptr;
		BVHNode* rightChild = nullptr;
		bool isLeaf;
		int primitiveStartIndex, primitiveEndIncludingIndex;
	};
}
#endif
