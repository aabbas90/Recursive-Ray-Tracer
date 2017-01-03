#include "triangle.h"
#include "infiniteplane.h"
#include<core/assert.h>
#include<rt/bbox.h>
#include <core/random.h>

namespace rt
{
	Triangle::Triangle(Point vertices[3], CoordMapper * texMapper, Material * material)
	{
		this->v1 = vertices[0];
		this->v2 = vertices[1];
		this->v3 = vertices[2];
		this->texMapper = texMapper;
		this->material = material;
	}

	Triangle::Triangle(const Point & v1, const Point & v2, const Point & v3, CoordMapper * texMapper, Material * material)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
		this->bbox = BBox(min(v1, v2), max(v1, v2));
		this->bbox.extend(v3);
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox Triangle::getBounds() const
	{
		return bbox;
	}

	Intersection Triangle::intersect(const Ray & ray, float previousBestDistance) const
	{
		Vector v1v2 = v2 - v1;
		Vector v1v3 = v3 - v1;
		Vector normalVector = cross(v1v2, v1v3);
		float fullArea = normalVector.length() / 2;

		InfinitePlane plane = InfinitePlane(v1, normalVector.normalize(), texMapper, material);
		Intersection planeInt = plane.intersect(ray, previousBestDistance);
		Intersection intObject;

		if (planeInt)
		{
			
			Point p = planeInt.hitPoint();

			Vector v3v2 = v3 - v2;
			Vector pv2 = p - v2;

			Vector v3v2pNormal = cross(v3v2, pv2);
			float u = (v3v2pNormal.length() / 2) / fullArea;
			if (dot(normalVector, v3v2pNormal) < 0)
				return Intersection();

			Vector pv3 = p - v3;
			Vector v1v3pNormal = cross(pv3, v1v3);
			float v = (v1v3pNormal.length() / 2) / fullArea;
			if (dot(normalVector, v1v3pNormal) < 0)
				return Intersection();

			float w = 1 - u - v;

			if (w < 0 || w > 1)
				return Intersection();

			intObject = Intersection(planeInt.distance, ray, this, normalVector);
			intObject.SetLocalIntersectingPoint(u * v1 + v * v2 + w * v3);
		}

		return intObject;
	}

	Point Triangle::sample() const
	{
		// http://math.stackexchange.com/questions/18686/uniform-random-point-in-triangle
		float r1 = random();
		float r2 = random();
		float r3 = random();
		float r1Root = std::sqrt(r1);
		return (1 - r1Root) * v1 + (r1Root * (1 - r2)) * v2 + (r2 * r1Root) * v3;
	}

	float Triangle::getArea() const
	{
		Vector v1v2 = v2 - v1;
		Vector v1v3 = v3 - v1;
		Vector normalVector = cross(v1v2, v1v3);
		return normalVector.length() / 2;
	}
}