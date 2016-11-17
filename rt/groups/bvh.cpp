#include "bvh.h"
#include<rt/bbox.h>
#include<rt/intersection.h>

namespace rt
{
	BVH::BVH()
	{
		root = new Node();
	}
	BBox BVH::getBounds() const
	{
		return BBox();
	}
	Intersection BVH::intersect(const Ray & ray, float previousBestDistance) const
	{
		return Intersection();
	}
	void BVH::rebuildIndex()
	{
		buildBVH(root, 0, unsortedList.size() - 1);
	}

	BVH::~BVH()
	{
	}

	void BVH::add(Primitive * p)
	{
		unsortedList.push_back(p);
		BBox currentBox = p->getBounds();
		root->extendBox(currentBox);
	}

	void BVH::setMaterial(Material * m)
	{
	}

	void BVH::setCoordMapper(CoordMapper * cm)
	{
	}

	void BVH::buildBVH(Node* parentNode, int startIndex, int endIncludingIndex)
	{
		int numElements = endIncludingIndex - startIndex + 1;
		if (numElements <= maxNumberElementsInLeaf)
		{
			parentNode->isLeaf = true;
			parentNode->primitiveStartIndex = startIndex;
			parentNode->primitiveEndIncludingIndex = endIncludingIndex;
			setBoundingBoxOfNode(parentNode, startIndex, endIncludingIndex);
		}
		else
		{
			parentNode->leftChild = new Node();
			parentNode->rightChild = new Node();
			auto splitDimensionAndLocation = parentNode->boundingBox.findGreatestDimensionAndMiddleLocation();
			int dimension = splitDimensionAndLocation.first;
			float location = splitDimensionAndLocation.second;
			int splittingIndex = getIndexFromPlaneLocation(startIndex, endIncludingIndex, dimension, location);
			setBoundingBoxOfNode(parentNode->leftChild, startIndex, splittingIndex);
			setBoundingBoxOfNode(parentNode->rightChild, splittingIndex + 1, endIncludingIndex);
			buildBVH(parentNode->leftChild, startIndex, splittingIndex);
			buildBVH(parentNode->rightChild, splittingIndex + 1, endIncludingIndex);
		}
	}
	
	int BVH::getIndexFromPlaneLocation(int startIndex, int endIncludingIndex, int dimensionIndex, float planeLocation)
	{
		auto startItr = unsortedList.begin() + startIndex;
		auto endItr = unsortedList.end() - (unsortedList.size() - endIncludingIndex - 1);
		std::sort(startItr, endItr, MyComp(dimensionIndex));	//TODO: This is splitting upon minCorner location, maybe centre is better?
		auto newItr = std::lower_bound(startItr, endItr, planeLocation, MyComp(dimensionIndex));
		 // TODO: Check if works
		return (newItr - startItr) + startIndex;
	}

	void BVH::setBoundingBoxOfNode(Node *node, int startIndex, int endIncludingIndex)
	{
		for (int i = startIndex; i <= endIncludingIndex; i++)
		{
			node->boundingBox.extend(unsortedList[i]->getBounds());
		}
	}

	MyComp::MyComp(int dimensionIndex) :dimensionIndex(dimensionIndex){}

	bool MyComp::operator()(const Primitive* l, const Primitive* r)
	{
		switch (dimensionIndex)
		{
			case 0: 
				return l->getBounds().minCorner.x < r->getBounds().minCorner.x;

			case 1:
				return l->getBounds().minCorner.y < r->getBounds().minCorner.y;

			case 2:
				return l->getBounds().minCorner.z < r->getBounds().minCorner.z;
			default:
			{
				throw;
			}
		}
	}

	bool MyComp::operator()(const Primitive* l, float valueToCompare)
	{
		switch (dimensionIndex)
		{
		case 0:
			return l->getBounds().minCorner.x < valueToCompare;

		case 1:
			return l->getBounds().minCorner.y < valueToCompare;

		case 2:
			return l->getBounds().minCorner.z < valueToCompare;

		default:
		{
			throw;
		}
	}
}
