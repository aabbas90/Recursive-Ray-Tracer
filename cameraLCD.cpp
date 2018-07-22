//#include "cameraLCD.h"
//#include <rt/solids/triangle.h>
//#include <rt/intersection.h>
//#include <core/assert.h>
//#include<rt/bbox.h>
//#include<core/random.h>
//
//namespace rt
//{
//	cameraLCD::cameraLCD(const Point & v1, const Vector & spanH, const Vector & spanV, float f, float angleX, float angleY, CoordMapper * texMapper, Material * material)
//	{
//		this->p1 = v1;
//		this->spanH = spanH;
//		this->spanV = spanV;
//		this->angleX = angleX;
//		this->angleY = angleY;
//		this->texMapper = texMapper;
//		this->material = material;
//
//		Point v2 = p1 + spanH;
//		this->box = BBox(min(v1, v2), max(v1, v2));
//		Point v3 = p1 + spanV;
//		this->box.extend(v3);
//		Point v4 = v3 + spanH;
//		this->box.extend(v4);
//		cameraCentre = (v1 + v2 + v3 + v4) * 0.25f;
//	}
//
//	BBox cameraLCD::getBounds() const
//	{
//		return box;
//	}
//
//	Intersection cameraLCD::intersect(const Ray & ray, float previousBestDistance) const
//	{
//		Point v1 = p1;
//		Point v2 = p1 + spanH;
//		Point v3 = p1 + spanV;
//		Point v4 = v3 + spanH;
//
//		Triangle tri1 = Triangle(v1, v2, v4, texMapper, material);
//		Intersection tri1Intersection = tri1.intersect(ray, previousBestDistance);
//		if (tri1Intersection)
//		{
//			Vector normal = tri1Intersection.normal();
//			if (dot(normal, ray.d) > 0)
//				normal = -1.0f * normal;
//
//			Intersection intersectionObject = Intersection(tri1Intersection.distance, ray, this, normal);
//			intersectionObject.SetLocalIntersectingPoint((ray.getPoint(tri1Intersection.distance) - cameraCentre).ToPoint());
//			return intersectionObject;
//		}
//
//		Triangle tri2 = Triangle(v1, v3, v4, texMapper, material);
//		Intersection tri2Intersection = tri2.intersect(ray, previousBestDistance);
//		if (tri2Intersection)
//		{
//			Vector normal = tri2Intersection.normal();
//			if (dot(normal, ray.d) > 0)
//				normal = -1.0f * normal;
//
//			Intersection intersectionObject = Intersection(tri2Intersection.distance, ray, this, normal);
//			intersectionObject.SetLocalIntersectingPoint((ray.getPoint(tri2Intersection.distance) - cameraCentre).ToPoint());
//			return intersectionObject;
//		}
//
//		return Intersection();
//	}
//
//	Point cameraLCD::sample() const
//	{
//		// http://stackoverflow.com/questions/240778/random-points-inside-a-polygon
//		return p1 + random() * spanH + random() * spanV;
//	}
//
//	float cameraLCD::getArea() const
//	{
//		return cross(spanH, spanV).length();
//	}
//
//	Ray cameraLCD::getCameraRay(Intersection intersection)
//	{
//		Ray newRay = Ray();
//		newRay.o = cameraCentre;
//		
//		Vector spanningH = spanH.normalize() * tan(angleX / 2.0f);
//		Vector spanningV = spanV.normalize() * tan(angleY / 2.0f);
//
//		Vector forwardVector = cross(spanH, spanV).normalize();
//		Point localIntersectionPoint = intersection.local();
//		Vector intersectionVector = Vector(localIntersectionPoint.x, localIntersectionPoint.y, localIntersectionPoint.z);
//		newRay.d = forwardVector + dot(intersectionVector, spanningH) * spanningH - dot(intersectionVector, spanningV) * spanningV;
//	}
//}