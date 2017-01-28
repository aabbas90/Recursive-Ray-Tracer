#include "striangle.h"
#include <core/assert.h>
#include <rt/solids/triangle.h>
#include <rt/solids/infiniteplane.h>
#include <rt/intersection.h>

namespace rt
{
	SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper * texMapper, Material * material)
	{
		this->v1 = vertices[0];
		this->v2 = vertices[1];
		this->v3 = vertices[2];

		nv1 = normals[0];
		nv2 = normals[1];
		nv3 = normals[2];
		
		this->bbox = BBox(min(v1, v2), max(v1, v2));
		this->bbox.extend(v3);

		this->texMapper = texMapper;
		this->material = material;
	}

	SmoothTriangle::SmoothTriangle(const Point & v1, const Point & v2, const Point & v3, const Vector & n1, const Vector & n2, const Vector & n3, CoordMapper * texMapper, Material * material)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;

		nv1 = n1;
		nv2 = n2;
		nv3 = n3;

		this->bbox = BBox(min(v1, v2), max(v1, v2));
		this->bbox.extend(v3);

		this->texMapper = texMapper;
		this->material = material;
	}

	Intersection SmoothTriangle::intersect(const Ray & ray, float previousBestDistance) const
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

			if (dot(normalVector, ray.d.normalize()) > 0)
				normalVector = -1.0f * normalVector;

			Vector interpolatedNormal = u * nv1 + v * nv2 + w * nv3;
			intObject = Intersection(planeInt.distance, ray, this, interpolatedNormal);
			intObject.SetLocalIntersectingPoint(u * v1 + v * v2 + w * v3);
		}

		return intObject;
	}
}