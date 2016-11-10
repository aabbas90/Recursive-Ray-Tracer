#ifndef CG1RAYTRACER_INTERSECTION_HEADER
#define CG1RAYTRACER_INTERSECTION_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <rt/ray.h>

namespace rt {

class Solid;

class Intersection {
public:
	Ray ray;
	const Solid* solid;
	float distance;

	Intersection() {}
	static Intersection failure();

	Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal);

	Point hitPoint() const;
	Vector normal() const;
	Point local() const;
	void SetLocalIntersectingPoint(const Vector& vector);
	void SetLocalIntersectingPoint(const Point& point);

	operator bool(); //this allows intersection object to be put directly in conditional statements. Becomes true iff there is an intersection

private:
	Vector normalVector; // This is normalized
	bool foundIntersection = false;
	Point globalIntersectionPoint;
	Point localIntersectionPoint;
};

}

#endif
