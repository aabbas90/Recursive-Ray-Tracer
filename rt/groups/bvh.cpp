#include "bvh.h"
#include<rt/bbox.h>
#include<rt/intersection.h>
#include<tuple>

namespace rt
{
	BVH::BVH(bool doSAH)
	{
		root = new BVHNode();
		this->doSAH = doSAH;
	}
	BBox BVH::getBounds() const
	{
		if(root)
			return root->boundingBox;
		else
			return BBox();
	}
	Intersection BVH::intersect(const Ray & ray, float previousBestDistance) const
	{
		return intersectNode(ray, previousBestDistance, root);
	}
	Intersection BVH::intersectNode(const Ray & ray, float previousBestDistance, BVHNode* node) const
	{
		if (node == nullptr)
		{
			return Intersection();
		}
		auto t1t2 = node->boundingBox.intersect(ray);
		bool isIntersected = std::get<2>(t1t2);
		float minT = std::abs(std::get<0>(t1t2));
		if (!isIntersected || minT > previousBestDistance)
		{
			return Intersection();
		}
		if (node->isLeaf)
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
			if (smallestIntersection)
			{
				return smallestIntersection;
			}
			else
			{
				return Intersection();
			}

		}
		else if (!node->isLeaf)
		{
			Intersection leftIntersection = intersectNode(ray, previousBestDistance, node->leftChild);
			Intersection rightIntersection = intersectNode(ray, previousBestDistance, node->rightChild);
			if (leftIntersection && rightIntersection)
			{
				if (leftIntersection.distance < rightIntersection.distance)
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
			else if (leftIntersection && !rightIntersection)
			{
				if (leftIntersection.distance < previousBestDistance)
					return leftIntersection;
				else
					return Intersection();
			}
			else if (!leftIntersection && rightIntersection)
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
		for (int i = 0; i < unsortedList.size(); i++)
		{
			unsortedList[i]->setMaterial(m);
		}
	}

	void BVH::setCoordMapper(CoordMapper * cm)
	{
		for (int i = 0; i < unsortedList.size(); i++)
		{
			unsortedList[i]->setCoordMapper(cm);
		}
	}

	void BVH::buildBVH(BVHNode* parentNode, int startIndex, int endIncludingIndex)
	{
		int numElements = endIncludingIndex - startIndex + 1;
		if (numElements < 0)
			throw;

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
			int splittingIndex;
			if (!doSAH)
			{
				auto splitDimensionAndLocation = parentNode->boundingBox.findGreatestDimensionAndMiddleLocation();
				int dimension = splitDimensionAndLocation.first;
				float location = splitDimensionAndLocation.second;
				splittingIndex = getIndexFromPlaneLocation(startIndex, endIncludingIndex, dimension, location);
				if (splittingIndex >= endIncludingIndex || splittingIndex <= 0)
				{
					splittingIndex = (startIndex + endIncludingIndex) / 2;
				}
			}

			else
			{
				auto splittingIndexAndDimension = getSplittingIndexAndDimensionSAH(startIndex, endIncludingIndex);
				splittingIndex = splittingIndexAndDimension.first;
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
		auto endItr = unsortedList.end() - (unsortedList.size() - endIncludingIndex) + 1;
		std::sort(startItr, endItr, PrimitiveComparator(dimensionIndex));	//TODO: This is splitting upon minCorner location, maybe centre is better?
		auto newItr = std::lower_bound(startItr, endItr, planeLocation, PrimitiveComparator(dimensionIndex));
		//// TODO: Check if works
		return (newItr - startItr) + startIndex - 1;
		//std::cout << itrSI << std::endl;
		//return splittingIndex + 1;
	}

	void BVH::setBoundingBoxOfNode(BVHNode *node, unsigned int startIndex, unsigned int endIncludingIndex)
	{
		for (int i = startIndex; i <= endIncludingIndex; i++)
		{
			node->boundingBox.extend(unsortedList[i]->getBounds());
		}
	}

	std::pair<int, int> BVH::getSplittingIndexAndDimensionSAH(int startIndex, int endIncludingIndex)
	{
		int minCostIndex;
		int minCostDimension;
		float minCost = maxFloat;
		auto startItr = unsortedList.begin() + startIndex;
		auto endItr = unsortedList.end() - (unsortedList.size() - endIncludingIndex);
		BBox bigBox = getBBoxOfPrimitives(startIndex, endIncludingIndex);
		for (int dimensionIndex = 0; dimensionIndex < 3; dimensionIndex++)
		{
			std::sort(startItr, endItr, PrimitiveComparator(dimensionIndex));
			float totalDistance;
			float startLocation;
			if (dimensionIndex == 0)
			{
				startLocation = bigBox.minCorner.x;
				totalDistance = bigBox.getXLength();
			}
			else if (dimensionIndex == 1)
			{
				startLocation = bigBox.minCorner.y;
				totalDistance = bigBox.getYLength();
			}
			else if (dimensionIndex == 2)
			{
				startLocation = bigBox.minCorner.z;
				totalDistance = bigBox.getZLength();
			}

			for (int currentBin = 1; currentBin <= numberBins; currentBin++)
			{
				float leftDistance = totalDistance * currentBin / numberBins;
				// float rightDistance = totalDistance * (numberBins - currentBin) / numberBins;
				float splitLocation = startLocation + leftDistance;
				auto newItr = std::lower_bound(startItr, endItr, splitLocation, PrimitiveComparator(dimensionIndex));
				
				int splitIndex = (newItr - startItr) + startIndex - 1;

				int numberPrimitivesLeft = splitIndex - startIndex + 1;
				int numberPrimitivesRight = endIncludingIndex - splitIndex;

				BBox bboxLeft = getBBoxOfPrimitives(startIndex, splitIndex);
				BBox bboxRight = getBBoxOfPrimitives(splitIndex + 1, endIncludingIndex);

				float currentCost = numberPrimitivesLeft *  bboxLeft.getSurfaceArea() / bigBox.getSurfaceArea() +
					numberPrimitivesRight * bboxRight.getSurfaceArea() / bigBox.getSurfaceArea();

				if (currentCost < minCost)
				{
					minCostDimension = dimensionIndex;
					minCostIndex = splitIndex;
					minCost = currentCost;
				}
			}
		}

		std::sort(startItr, endItr, PrimitiveComparator(minCostDimension));
		return std::pair<int, int>(minCostIndex, minCostDimension);
	}

	BBox BVH::getBBoxOfPrimitives(int startIndex, int endIncludingIndex)
	{
		BBox box;
		for (int i = startIndex; i <= endIncludingIndex; i++)
		{
			box.extend(unsortedList[i]->getBounds());
		}
		return box;
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
