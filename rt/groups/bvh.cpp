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
			for (unsigned int i = node->primitiveStartIndex; i < node->primitiveEndIncludingIndex; ++i)
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


	// Intersection BVH::intersect(const Ray & ray, float previousBestDistance) const
	// {
	// 	std::cout << "--------new ray----------\n";
	// 	BVHNode* currentNode = root;
	// 	Ray localRay = ray;
	// 	auto t1t2 = currentNode->boundingBox.intersect(ray);
	// 	if (t1t2.first > t1t2.second || t1t2.first > previousBestDistance)
	// 	{
	// 		return Intersection();
	// 	}
	// 	std::priority_queue<IntersectionElement> pqueue;
	// 	int count = 0;
	// 	while(true)
	// 	{
	// 		count++;
	// 		if (count > 1000)
	// 		{
	// 			return Intersection(); //TODO WORKAROUND, find a way to return
	// 		}
	// 		std::cout << count << "\n";
	// 		Intersection smallestIntersection;
	// 		if(!currentNode->isLeaf)
	// 		{
	// 			std::pair<float, float> t1t2Left, t1t2Right;
	// 			if(currentNode->leftChild != nullptr)
	// 				t1t2Left = currentNode->leftChild->boundingBox.intersect(localRay);
	// 			if(currentNode->rightChild != nullptr)
	// 				t1t2Right = currentNode->rightChild->boundingBox.intersect(localRay);
	// 			if(currentNode->leftChild != nullptr && t1t2Left.first < t1t2Left.second && currentNode->rightChild != nullptr &&  t1t2Right.first < t1t2Right.second)
	// 			{
	// 				if(t1t2Left.first > t1t2Right.first) //closest is right child
	// 				{
	// 					pqueue.push(IntersectionElement(currentNode->leftChild, t1t2.first, true));
	// 					currentNode = currentNode->rightChild;
	// 					std::cout << "pushed left" << "\n";
	// 				}
	// 				else
	// 				{
	// 					pqueue.push(IntersectionElement(currentNode->rightChild, t1t2.first, true));
	// 					std::cout << "pushed right" << "\n";
	// 					currentNode = currentNode->leftChild;
	// 				}
	// 			}
	// 			else if((currentNode->leftChild != nullptr  && t1t2Left.first < t1t2Left.second) && (currentNode->rightChild == nullptr || t1t2Right.first > t1t2Right.second)) //only left intersects
	// 			{
	// 				currentNode = currentNode->leftChild;
	// 			}
	// 			else if((currentNode->leftChild == nullptr || t1t2Left.first > t1t2Left.second )&& (currentNode->rightChild != nullptr && t1t2Right.first < t1t2Right.second))//only right intersects
	// 			{
	// 				currentNode = currentNode->rightChild;
	// 			}
	// 		}
	// 		else //if  leaf
	// 		{
				
	// 			for (int i = currentNode->primitiveStartIndex; i < currentNode->primitiveEndIncludingIndex; i++)
	// 			{
	// 				Intersection intersection = unsortedList[i]->intersect(localRay, previousBestDistance);
	// 				if (intersection && (intersection.distance < previousBestDistance))
	// 				{
	// 					smallestIntersection = intersection;
	// 					previousBestDistance = intersection.distance;
	// 				}
	// 			}
	// 			//if (smallestIntersection)	
	// 		} // endif
	// 		auto qsize = pqueue.size();
	// 		while(pqueue.size() != 0)
	// 		{
	// 			std::cout << "INNER WHILE" << "\n";
	// 			if(pqueue.top().nodeDistance < previousBestDistance)
	// 			{
	// 				currentNode = pqueue.top().node;
	// 				pqueue.pop();
	// 				std::cout << "POP" << "\n";
	// 				break;
	// 			}
	// 			std::cout << "POP" << "\n";
	// 			pqueue.pop();
	// 			if(pqueue.size() == 0)
	// 			{
	// 				return smallestIntersection;
	// 			}
	// 		}
	// 		if(smallestIntersection)
	// 			return smallestIntersection;
	// 	}
	// }




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

	// Intersection BVH::IterateOverQueue(std::priority_queue<IntersectionElement>& pqueue, const Ray & ray, float previousBestDistance) const
	// {
	// 	if (pqueue.empty())
	// 		return Intersection();

	// 	IntersectionElement currentElement = pqueue.top();
	// 	pqueue.pop();
	// 	if (currentElement.node->isLeaf)
	// 	{
	// 		Intersection smallestIntersection;
	// 		for (int i = currentElement.node->primitiveStartIndex; i <= currentElement.node->primitiveEndIncludingIndex; i++)
	// 		{
	// 			Intersection intersection = unsortedList[i]->intersect(ray, previousBestDistance);
	// 			if (intersection && (intersection.distance < previousBestDistance))
	// 			{
	// 				smallestIntersection = intersection;
	// 				previousBestDistance = intersection.distance;
	// 			}
	// 		}
	// 		if (smallestIntersection)
	// 			return smallestIntersection;
	// 	}

	// 	// if not reached the leaf:
	// 	else
	// 	{
	// 		std::vector<BVHNode> nodesToIterate;
	// 		if(currentElement.node->leftChild != nullptr)
	// 			nodesToIterate.push_back(*(currentElement.node->leftChild));
	// 		if(currentElement.node->rightChild != nullptr)
	// 			nodesToIterate.push_back(*(currentElement.node->rightChild));

	// 		for (BVHNode currentChild : nodesToIterate)
	// 		{
	// 			auto t1t2 = currentChild.boundingBox.intersect(ray);
	// 			if (t1t2.first < t1t2.second || t1t2.first < previousBestDistance)
	// 			{
	// 				IntersectionElement currentChildElement = IntersectionElement(&currentChild, t1t2.first, true);
	// 				pqueue.push(currentChildElement);
	// 			}
	// 		}
	// 	}
	// 	auto currentSize = pqueue.size();
	// 	std::cout << "pqueue size = " << currentSize << "\n";
	// 	return IterateOverQueue(pqueue, ray, previousBestDistance);
	// }
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
