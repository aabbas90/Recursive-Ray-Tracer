#include "bvh.h"
#include<rt/bbox.h>
#include<rt/intersection.h>
#include<tuple>

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
		return intersectNode(ray, previousBestDistance, root);
	}
	Intersection BVH::intersectNode(const Ray & ray, float previousBestDistance, BVHNode* node) const 
	{
		if(node == nullptr)
		{
			return Intersection();
		}
		auto t1t2 = node->boundingBox.intersect(ray);
		bool isIntersected = std::get<2>(t1t2);
		float minT = std::get<0>(t1t2);
		if (!isIntersected || minT > previousBestDistance)
		{
			return Intersection();
		}
		if(node->isLeaf)
		{
			Intersection smallestIntersection;
			for (unsigned int i = node->primitiveStartIndex; i <= node->primitiveEndIncludingIndex; ++i)
			{
				Intersection intersection = unsortedList[i]->intersect(ray, previousBestDistance);
				if (intersection && (intersection.distance < previousBestDistance))
				{
					smallestIntersection = intersection;
					previousBestDistance = intersection.distance;
				}
			}
			if(smallestIntersection)
			{
				return smallestIntersection;
			}
			else
			{
				return Intersection();
			}
			
		}
		else if(!node->isLeaf)
		{
			Intersection leftIntersection = intersectNode(ray, previousBestDistance, node->leftChild);
			Intersection rightIntersection = intersectNode(ray, previousBestDistance, node->rightChild);
			if(leftIntersection && rightIntersection)
			{
				if(leftIntersection.distance < rightIntersection.distance)
				{
					if (leftIntersection.distance < previousBestDistance)
						return leftIntersection;
					else
						return Intersection();
				}
				else
				{
					if (rightIntersection.distance < previousBestDistance)
						return rightIntersection;
					else
						return Intersection();
				}
			}
			else if(leftIntersection && !rightIntersection)
			{
					if (leftIntersection.distance < previousBestDistance)
						return leftIntersection;
					else
						return Intersection();
			}
			else if(!leftIntersection && rightIntersection)
			{
					if (rightIntersection.distance < previousBestDistance)
						return rightIntersection;
					else
						return Intersection();
			}
			else
			{
				return Intersection();
			}
		} //end else if(!node->isLeaf)
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
			numNodes += 2; 
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
