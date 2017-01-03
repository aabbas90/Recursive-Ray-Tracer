#include "quad.h"
#include "triangle.h"
#include <rt/intersection.h>
#include <core/assert.h>
#include<rt/bbox.h>
#include<core/random.h>

namespace rt
{
	Quad::Quad(const Point & v1, const Vector & span1, const Vector & span2, CoordMapper * texMapper, Material * material)
	{
		this->p1 = v1;
		this->span1 = span1;
		this->span2 = span2;
		this->texMapper = texMapper;
		this->material = material;
		Point v2 = p1 + span1;
		this->box = BBox(min(v1, v2), max(v1, v2));
		Point v3 = p1 + span2;
		this->box.extend(v3);
		Point v4 = v3 + span1;
		this->box.extend(v4);
	}

	BBox Quad::getBounds() const
	{
		return box;
	}

	Intersection Quad::intersect(const Ray & ray, float previousBestDistance) const
	{
		Point v1 = p1;
		Point v2 = p1 + span1;
		Point v3 = p1 + span2;
		Point v4 = v3 + span1;

		Triangle tri1 = Triangle(v1, v2, v4, texMapper, material);
		Intersection tri1Intersection = tri1.intersect(ray, previousBestDistance);
		if (tri1Intersection)
		{
			Intersection intersectionObject = Intersection(tri1Intersection.distance, ray, this, tri1Intersection.normal());
			intersectionObject.SetLocalIntersectingPoint((ray.getPoint(tri1Intersection.distance) - v1).ToPoint());
			return intersectionObject;
		}

		Triangle tri2 = Triangle(v1, v3, v4, texMapper, material);
		Intersection tri2Intersection = tri2.intersect(ray, previousBestDistance);
		if (tri2Intersection)
		{
			Intersection intersectionObject = Intersection(tri2Intersection.distance, ray, this, tri2Intersection.normal());
			intersectionObject.SetLocalIntersectingPoint((ray.getPoint(tri2Intersection.distance) - v1).ToPoint());
			return intersectionObject;
		}

		return Intersection();
	}

	Point Quad::sample() const
	{
		// http://stackoverflow.com/questions/240778/random-points-inside-a-polygon
		return p1 + random() * span1 + random() * span2;
	}

	float Quad::getArea() const
	{
		return cross(span1, span2).length();
	}
}