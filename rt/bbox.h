#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>


extern const float maxFloat;
extern const float minFloat;

namespace rt {

class Ray;

class BBox {
public:
	Point minCorner, maxCorner;
	bool isEmpty = true;
	BBox() {}
	BBox(const Point& minP, const Point& maxP) 
	{
		this->minCorner = min(minP, maxP);
		this->maxCorner = max(minP, maxP);
		this->isEmpty = false; 
	}
	static BBox empty();
	static BBox full();

	void extend(const Point& point);
	void extend(const BBox& bbox);
	void Inflate(float factor);

	Vector diagonal() const {
		if (this->isEmpty)
			return Vector(0, 0, 0);
		else
			return maxCorner - minCorner;
	}

<<<<<<< HEAD
	std::tuple<float, float, bool> intersect(const Ray& ray) const;
=======
	std::tuple< float, float, bool> intersect(const Ray & ray) const;
>>>>>>> chitra

	bool isUnbound();
	static bool isInside(BBox& parent, BBox& child);
	std::pair<int, float> findGreatestDimensionAndMiddleLocation();
	float getSurfaceArea();
	float getXLength();
	float getYLength();
	float getZLength();

};

}


#endif
