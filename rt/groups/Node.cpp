#include<rt/groups/Node.h>

namespace rt
{
	Node::Node()
	{
		boundingBox = BBox::empty();
		isLeaf = false;
		leftChild = NULL;
		rightChild = NULL;
	}

	void Node::extendBox(const BBox& inputBox)
	{
		boundingBox.extend(inputBox);
	}
}