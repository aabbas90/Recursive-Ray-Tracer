#include "triangle.h"
#include "infiniteplane.h"
#include<core/assert.h>
#include<rt/bbox.h>

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
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox Triangle::getBounds() const
	{
		BBox bbox = BBox(v1, v2);
		bbox.extend(v3);
		return bbox;
	}

	Intersection Triangle::intersect(const Ray & ray, float previousBestDistance) const
	{
		Vector v1v2 = v2 - v1;
		Vector v1v3 = v3 - v1;
		Vector normalVector = cross(v1v2, v1v3);
		float fullArea = normalVector.length() / 2;

		InfinitePlane plane = InfinitePlane(v1, normalVector.normalize(), texMapper, material);
		Intersection intersectionObject = plane.intersect(ray, previousBestDistance);

		if (intersectionObject)
		{
			Point p = intersectionObject.hitPoint();

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

			intersectionObject.SetLocalIntersectingPoint(u * v1 + v * v2 + w * v3);
		}

		return intersectionObject;
	}

	Point Triangle::sample() const
	{
		NOT_IMPLEMENTED;
	}

	float Triangle::getArea() const
	{
		Vector v1v2 = v2 - v1;
		Vector v1v3 = v3 - v1;
		Vector normalVector = cross(v1v2, v1v3);
		return normalVector.length() / 2;
	}
}