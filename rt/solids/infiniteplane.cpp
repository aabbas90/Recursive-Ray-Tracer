#include <rt/solids/infiniteplane.h>
#include <core/assert.h>
#include <rt/bbox.h>

namespace rt
{
	InfinitePlane::InfinitePlane(const Point & origin, const Vector & normal, CoordMapper * texMapper, Material * material)
	{
		this->origin = origin;
		this->normal = normal;
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox InfinitePlane::getBounds() const
	{
		Vector normalizedNormal = normal.normalize();
		Vector xSpanningVector = Vector(1, 0, 0);
		Vector ySpanningVector = Vector(0, 1, 0);
		if (dot(xSpanningVector, normalizedNormal) != 1)
		{
			ySpanningVector = cross(normalizedNormal, xSpanningVector).normalize();
			xSpanningVector = cross(ySpanningVector, normalizedNormal).normalize();
		}
		else
		{
			xSpanningVector = cross(ySpanningVector, normalizedNormal).normalize();
			ySpanningVector = cross(normalizedNormal, xSpanningVector).normalize();
		}
		Point v1 = (maxFloat * xSpanningVector).ToPoint();
		Point v2 = (minFloat * xSpanningVector).ToPoint();
		BBox box = BBox(v1, v2);
		Point v3 = (maxFloat * ySpanningVector).ToPoint();
		Point v4 = (minFloat * ySpanningVector).ToPoint();
		box.extend(v3);
		box.extend(v4);
		return box;
	}

	Intersection InfinitePlane::intersect(const Ray & ray, float previousBestDistance) const
	{
		float denom = dot(normal, ray.d);
		if (std::abs(denom) > 1e-6) 
		{
			float currentDistance = dot(origin - ray.o, normal) / denom;
			if (currentDistance < previousBestDistance && currentDistance > 0)
			{
				Intersection intersect = Intersection(currentDistance, ray, this, normal);
				intersect.SetLocalIntersectingPoint((ray.getPoint(currentDistance) - origin).ToPoint());
				return intersect;
			}
		}

		return Intersection();
	}

	Point InfinitePlane::sample() const
	{
		NOT_IMPLEMENTED;
	}

	float InfinitePlane::getArea() const
	{
		return FLT_MAX;
	}

	Quadric* InfinitePlane::ToQuadric()
	{
		float G = normal.x;
		float H = normal.y;
		float I = normal.z;
		float J = -(G * origin.x + H * origin.y + I * origin.z);
		return new Quadric(0, 0, 0, 0, 0, 0, G, H, I, J, texMapper, material);
	}
}