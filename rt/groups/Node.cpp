#include<rt/groups/Node.h>

namespace rt
{
	BVHNode::BVHNode()
	{
		boundingBox = BBox::empty();
		isLeaf = false;
		leftChild = NULL;
		rightChild = NULL;
	}

	void BVHNode::extendBox(const BBox& inputBox)
	{
		boundingBox.extend(inputBox);
	}
}