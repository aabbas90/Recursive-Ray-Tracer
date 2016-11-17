#ifndef CG1RAYTRACER_GROUPS_NODE_HEADER
#define CG1RAYTRACER_GROUPS_NODE_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#define maxNumberOfChildren 3;
namespace rt
{
	class Node
	{

	public:
		Node();
		BBox boundingBox;
		void extendBox(const BBox& inputBox);
		Node* leftChild;
		Node* rightChild;
		bool isLeaf;
		int primitiveStartIndex, primitiveEndIncludingIndex;
	};
}
#endif
