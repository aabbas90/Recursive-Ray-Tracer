#include "bvh.h"
#include<rt/bbox.h>
#include<rt/solids/aabox.h>
#include<rt/intersection.h>
#include<tuple>
<<<<<<< HEAD
#include<iostream>
=======
>>>>>>> chitra

namespace rt
{
	BVH::BVH(bool doSAH)
	{
		root = new BVHNode();
		this->doSAH = doSAH;
	}
	BBox BVH::getBounds() const
	{
<<<<<<< HEAD
		return root->boundingBox;
	}
	//Intersection BVH::intersect(const Ray & ray, float previousBestDistance) const
	//{
	//	Intersection smallestIntersection;
	//	for (int i = 0; i < unsortedList.size(); i++)
	//	{
	//		auto box = unsortedList[i]->getBounds();
	//		auto t1t2 = box.intersect(ray);
	//		bool isIntersected = std::get<2>(t1t2);
	//		float minT = std::get<0>(t1t2);

	//		if (!isIntersected || minT > previousBestDistance)
	//			continue;

	//		Intersection intersection = unsortedList[i]->intersect(ray, previousBestDistance);
	//		if (intersection && (intersection.distance < previousBestDistance) && intersection.distance > 0)
	//		{
	//			smallestIntersection = intersection;
	//			previousBestDistance = intersection.distance;
	//		}
	//	}
	//	return smallestIntersection;
	//}

	Intersection BVH::intersect(const Ray & ray, float previousBestDistance) const
	{
		BVHNode* currentNode = root;
		auto t1t2 = currentNode->boundingBox.intersect(ray);
		bool isIntersected = std::get<2>(t1t2);
		float minT = std::get<0>(t1t2);

		if (!isIntersected || minT > previousBestDistance)
		{
			return Intersection();
		}

		std::priority_queue<IntersectionElement> pqueue;
		pqueue.push(IntersectionElement(currentNode, minT, true));
		Intersection smallestIntersection;

		while(pqueue.size() != 0)
		{
			auto currentElement = pqueue.top();
			currentNode = currentElement.node;
			pqueue.pop();
			
			if(!currentNode->isLeaf)
			{
				if (currentNode->leftChild != nullptr && !currentNode->leftChild->boundingBox.isEmpty)
				{
					auto t1t2Left = currentNode->leftChild->boundingBox.intersect(ray);
					bool isIntersected = std::get<2>(t1t2Left);
					float minT = std::get<0>(t1t2Left);

					if (!isIntersected || minT > previousBestDistance)
						continue;

					pqueue.push(IntersectionElement(currentNode->leftChild, minT, true));
				}
				if (currentNode->rightChild != nullptr && !currentNode->rightChild->boundingBox.isEmpty)
				{
					auto t1t2Right = currentNode->rightChild->boundingBox.intersect(ray);
					bool isIntersected = std::get<2>(t1t2Right);
					float minT = std::get<0>(t1t2Right);

					if (!isIntersected || minT > previousBestDistance)
						continue;

					pqueue.push(IntersectionElement(currentNode->rightChild, minT, true));
=======
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
>>>>>>> chitra
				}
			}
			if (smallestIntersection)
			{
<<<<<<< HEAD
				BBox bbox = currentElement.node->boundingBox;
				AABox aabox = AABox(bbox.minCorner, bbox.maxCorner, nullptr, nullptr);
				Intersection intersection = aabox.intersect(ray, previousBestDistance);
				if (intersection && (intersection.distance < previousBestDistance) && intersection.distance > 0)
				{
					smallestIntersection = intersection;
					previousBestDistance = intersection.distance;
				}

				/*for (int i = currentNode->primitiveStartIndex; i <= currentNode->primitiveEndIncludingIndex; i++)
				{
					Intersection intersection = unsortedList[i]->intersect(ray, previousBestDistance);
					if (intersection && (intersection.distance < previousBestDistance) && intersection.distance > 0)
					{
						smallestIntersection = intersection;
						previousBestDistance = intersection.distance;
					}
				}*/
			}
		}

		return smallestIntersection;
	}

	// Intersection BVH::intersect(const Ray & ray, float previousBestDistance) const
	// {
	// 	std::cout << "new ray--------------------------------------\n";
	// 	auto t1t2 = root->boundingBox.intersect(ray);
	// 	if (t1t2.first > t1t2.second || t1t2.first > previousBestDistance)
	// 	{
	// 		return Intersection();
	// 	}
	// 	else
	// 	{
	// 		std::priority_queue<IntersectionElement> pqueue;
	// 		pqueue.push(IntersectionElement(root, t1t2.first, true));
	// 		Intersection bestIntersection = IterateOverQueue(pqueue, ray, previousBestDistance);
	// 		return bestIntersection;
	// 	}
	// }
=======
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
>>>>>>> chitra

	void BVH::rebuildIndex()
	{
		buildBVH(root, 0, unsortedList.size() - 1);
		int* count = new int[unsortedList.size()];
		for (int i = 0;  i < unsortedList.size();  i++)
		{
			count[i] = 0;
		}
		bool check = SanityCheck(root, count);
		for (int i = 0; i < unsortedList.size(); i++)
		{
			if (count[i] != 1)
			{
				throw;
			}
		}
	}

	BVH::~BVH()
	{
	}

	bool BVH::SanityCheck(BVHNode* parent, int* count) 
	{
		BBox currentBox = parent->boundingBox;
		if (!parent->isLeaf)
		{
			if (parent->leftChild != nullptr)
			{
				BBox leftBox = parent->leftChild->boundingBox;
				if (!BBox::isInside(currentBox, leftBox))
				{
					throw;
				}
				SanityCheck(parent->leftChild, count);
			}

			if (parent->rightChild != nullptr)
			{
				BBox rightBox = parent->rightChild->boundingBox;

				if (!BBox::isInside(currentBox, rightBox))
				{
					throw;
				}
				SanityCheck(parent->rightChild, count);
			}
		}
		else
		{
			for (int i = parent->primitiveStartIndex; i <= parent->primitiveEndIncludingIndex; i++)
			{
				if (!BBox::isInside(currentBox, parent->boundingBox))
				{
					throw;
				}
				count[i]++;
			}
		}
		return true;
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

<<<<<<< HEAD
	void BVH::buildBVH(BVHNode* parentNode, const int startIndex, const int endIncludingIndex)
=======
	void BVH::buildBVH(BVHNode* parentNode, int startIndex, int endIncludingIndex)
>>>>>>> chitra
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
			if (splittingIndex > endIncludingIndex)
			{
				throw;
			}
			setBoundingBoxOfNode(parentNode->rightChild, splittingIndex + 1, endIncludingIndex);
			buildBVH(parentNode->leftChild, startIndex, splittingIndex);
			buildBVH(parentNode->rightChild, splittingIndex + 1, endIncludingIndex);
		}
	}

	int BVH::getIndexFromPlaneLocation(const int startIndex, const int endIncludingIndex, int dimensionIndex, float planeLocation)
	{
<<<<<<< HEAD
		//auto startItr = unsortedList.begin() + startIndex;
		//auto endItr = unsortedList.end() - (unsortedList.size() - endIncludingIndex - 1);
		//std::sort(startItr, endItr, PrimitiveComparator(dimensionIndex));	//TODO: This is splitting upon minCorner location, maybe centre is better?
		//auto newItr = std::lower_bound(startItr, endItr, planeLocation, PrimitiveComparator(dimensionIndex));
		//// TODO: Check if works
		//return (newItr - startItr) + startIndex - 1;
		if (endIncludingIndex >= unsortedList.size())
			throw;

		for (int i = startIndex; i <= endIncludingIndex; i++)
		{
			float minDistance = maxFloat;
			int minIndex;
			for (int j = i; j <= endIncludingIndex; j++)
			{
				try
				{
					BBox bounds = unsortedList[j]->getBounds(); 
					switch (dimensionIndex)
					{
					case 0:
						if ((bounds.minCorner.x + bounds.maxCorner.x) / 2 < minDistance)
						{
							minIndex = j;
							minDistance = (bounds.minCorner.x + bounds.maxCorner.x) / 2;
						}
						break;
					case 1:
						if ((bounds.minCorner.y + bounds.maxCorner.y) / 2 < minDistance)
						{
							minIndex = j;
							minDistance = (bounds.minCorner.y + bounds.maxCorner.y) / 2;
						}
						break;
					case 2:
						if ((bounds.minCorner.z + bounds.maxCorner.z) / 2 < minDistance)
						{
							minIndex = j;
							minDistance = (bounds.minCorner.z + bounds.maxCorner.z) / 2;
						}
						break;
					default:
						throw;
					}
				}
				catch(...)
				{
					std::cout << j; 
				}

			}
			auto temp = unsortedList[i];
			unsortedList[i] = unsortedList[minIndex];
			unsortedList[minIndex] = temp;
		}

		int splittingIndex = startIndex;
		for (int i = startIndex; i <= endIncludingIndex; i++)
		{
			BBox bounds = unsortedList[i]->getBounds();
			switch (dimensionIndex)
			{
			case 0:
				if ((bounds.minCorner.x + bounds.maxCorner.x) / 2 < planeLocation)
				{
					splittingIndex++;
				}
				break;

			case 1:
				if ((bounds.minCorner.y + bounds.maxCorner.y) / 2 < planeLocation)
				{
					splittingIndex++;
				}
				break;
			case 2:
				if ((bounds.minCorner.z + bounds.maxCorner.z) / 2 < planeLocation)
				{
					splittingIndex++;

				}
				break;
			default:
				throw;
			}
		}
		
		return splittingIndex + 1;
=======
		auto startItr = unsortedList.begin() + startIndex;
		auto endItr = unsortedList.end() - (unsortedList.size() - endIncludingIndex) + 1;
		std::sort(startItr, endItr, PrimitiveComparator(dimensionIndex));	//TODO: This is splitting upon minCorner location, maybe centre is better?
		auto newItr = std::lower_bound(startItr, endItr, planeLocation, PrimitiveComparator(dimensionIndex));
		//// TODO: Check if works
		return (newItr - startItr) + startIndex - 1;
		//std::cout << itrSI << std::endl;
		//return splittingIndex + 1;
>>>>>>> chitra
	}

	void BVH::setBoundingBoxOfNode(BVHNode *node, unsigned int startIndex, unsigned int endIncludingIndex)
	{
		for (int i = startIndex; i <= endIncludingIndex; i++)
		{
			node->boundingBox.extend(unsortedList[i]->getBounds());
		}
	}

<<<<<<< HEAD
	 
=======
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

>>>>>>> chitra
	PrimitiveComparator::PrimitiveComparator(int dimensionIndex) :dimensionIndex(dimensionIndex) {}

	/*bool PrimitiveComparator::operator()(const Primitive* l, const Primitive* r) const
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
	}*/

	bool PrimitiveComparator::operator()(const Primitive* l, const Primitive* r) const
	{
		BBox lBox = l->getBounds();
		BBox rBox = r->getBounds();
		if (lBox.isEmpty || lBox.isUnbound() || rBox.isEmpty || rBox.isUnbound())
			throw;

		switch (dimensionIndex)
		{
		case 0:
			return lBox.minCorner.x + lBox.maxCorner.x < rBox.minCorner.x + rBox.maxCorner.x;
			break;
		case 1:
			return lBox.minCorner.y + lBox.maxCorner.y < rBox.minCorner.y + rBox.maxCorner.y;
			break;
		case 2:
			return lBox.minCorner.z + lBox.maxCorner.z < rBox.minCorner.z + rBox.maxCorner.z;
			break;
		default:
			throw;
		}
	}

	bool PrimitiveComparator::operator()(const Primitive* l, float valueToCompare) const
	{
		auto bounds = l->getBounds();
		if (bounds.isEmpty || bounds.isUnbound())
			throw;

		switch (dimensionIndex)
		{
		case 0:
			return (bounds.minCorner.x + bounds.maxCorner.x) / 2 < valueToCompare;
			break;
		case 1:
			return (bounds.minCorner.y + bounds.maxCorner.y) / 2  < valueToCompare;
			break;
		case 2:
			return (bounds.minCorner.z + bounds.maxCorner.z) / 2  < valueToCompare;
			break;
		default:
			throw;
		}
	}
}
