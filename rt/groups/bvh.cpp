#include "bvh.h"
#include<rt/bbox.h>
#include<rt/intersection.h>

namespace rt
{
	BVH::BVH()
	{
		root = new BVHNode();
	}
	BBox BVH::getBounds() const
	{
		return BBox();
	}

	Intersection BVH::intersect(const Ray & ray, float previousBestDistance) const
	{
		auto t1t2 = root->boundingBox.intersect(ray);
		if (t1t2.first > t1t2.second || t1t2.first > previousBestDistance)
		{
			return Intersection();
		}
		else
		{
			std::priority_queue<IntersectionElement> pqueue;
			pqueue.push(IntersectionElement(root, t1t2.first, true));
			Intersection bestIntersection = IterateOverQueue(pqueue, ray, previousBestDistance);
			return bestIntersection;
		}
	}

	Intersection BVH::IterateOverQueue(std::priority_queue<IntersectionElement> pqueue, const Ray & ray, float previousBestDistance) const
	{
		if (pqueue.empty())
			return Intersection();

		IntersectionElement currentElement = pqueue.top();
		pqueue.pop();
		if (currentElement.node->isLeaf)
		{
			Intersection smallestIntersection;
			for (int i = currentElement.node->primitiveStartIndex; i <= currentElement.node->primitiveEndIncludingIndex; i++)
			{
				Intersection intersection = unsortedList[i]->intersect(ray, previousBestDistance);
				if (intersection && (intersection.distance < previousBestDistance))
				{
					smallestIntersection = intersection;
					previousBestDistance = intersection.distance;
				}
			}
			if (smallestIntersection)
				return smallestIntersection;
		}

		// if not reached the leaf:
		else
		{
			std::vector<BVHNode> nodesToIterate;
			if(currentElement.node->leftChild != nullptr)
				nodesToIterate.push_back(*(currentElement.node->leftChild));
			if(currentElement.node->rightChild != nullptr)
				nodesToIterate.push_back(*(currentElement.node->rightChild));

			for (BVHNode currentChild : nodesToIterate)
			{
				auto t1t2 = currentChild.boundingBox.intersect(ray);
				if (t1t2.first < t1t2.second || t1t2.first < previousBestDistance)
				{
					IntersectionElement currentChildElement = IntersectionElement(&currentChild, t1t2.first, true);
					pqueue.push(currentChildElement);
				}
			}
		}

		return IterateOverQueue(pqueue, ray, previousBestDistance);
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

	void BVH::buildBVH(BVHNode* parentNode, unsigned int startIndex, unsigned int endIncludingIndex)
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
			parentNode->leftChild = new BVHNode();
			parentNode->rightChild = new BVHNode();
			auto splitDimensionAndLocation = parentNode->boundingBox.findGreatestDimensionAndMiddleLocation();
			int dimension = splitDimensionAndLocation.first;
			float location = splitDimensionAndLocation.second;
			int splittingIndex = getIndexFromPlaneLocation(startIndex, endIncludingIndex, dimension, location);
			if (splittingIndex >= endIncludingIndex || splittingIndex <= 0)
			{
				splittingIndex = (startIndex + endIncludingIndex) / 2;
			}
			setBoundingBoxOfNode(parentNode->leftChild, startIndex, splittingIndex);
			setBoundingBoxOfNode(parentNode->rightChild, splittingIndex + 1, endIncludingIndex);
			buildBVH(parentNode->leftChild, startIndex, splittingIndex);
			buildBVH(parentNode->rightChild, splittingIndex + 1, endIncludingIndex);
		}
	}

	int BVH::getIndexFromPlaneLocation(unsigned int startIndex, unsigned int endIncludingIndex, int dimensionIndex, float planeLocation)
	{
		auto startItr = unsortedList.begin() + startIndex;
		auto endItr = unsortedList.end() - (unsortedList.size() - endIncludingIndex - 1);
		std::sort(startItr, endItr, PrimitiveComparator(dimensionIndex));	//TODO: This is splitting upon minCorner location, maybe centre is better?
		auto newItr = std::lower_bound(startItr, endItr, planeLocation, PrimitiveComparator(dimensionIndex));
		// TODO: Check if works
		return (newItr - startItr) + startIndex - 1;
	}

	void BVH::setBoundingBoxOfNode(BVHNode *node, unsigned int startIndex, unsigned int endIncludingIndex)
	{
		for (int i = startIndex; i <= endIncludingIndex; i++)
		{
			node->boundingBox.extend(unsortedList[i]->getBounds());
		}
	}


	PrimitiveComparator::PrimitiveComparator(int dimensionIndex) :dimensionIndex(dimensionIndex) {}

	bool PrimitiveComparator::operator()(const Primitive* l, const Primitive* r) const
	{
		BBox lBox = l->getBounds();
		BBox rBox = r->getBounds();
		switch (dimensionIndex)
		{
		case 0:
			return lBox.minCorner.x < rBox.minCorner.x;

		case 1:
			return lBox.minCorner.y < rBox.minCorner.y;

		case 2:
			return lBox.minCorner.z < rBox.minCorner.z;
		default:
			throw;
		}
	}

	bool PrimitiveComparator::operator()(const Primitive* l, float valueToCompare) const
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
			throw;
		}
	}
}
