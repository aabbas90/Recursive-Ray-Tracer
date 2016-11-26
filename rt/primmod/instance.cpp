#include <rt/primmod/instance.h>
#include <rt/bbox.h>
#include <core/assert.h>


namespace rt {

	Instance::Instance(Primitive* content)
	{
		this->Content = content;
		transformation = Matrix::identity();
	}   
	Primitive* Instance::content()
	{
		return this;
	}
	void Instance::reset()
	{
		transformation = Matrix::identity();
	}
	void Instance::translate(const Vector& t)
	{
		transformation[0][3] += t.x;
		transformation[1][3] += t.y;
		transformation[2][3] += t.z;
	}
	void Instance::rotate(const Vector& axis, float angle)
	{
		Vector u = axis.normalize();
		Matrix rotation = Matrix(
			Float4(cos(angle) + u.x * u.x * (1 - cos(angle)), u.x * u.y * (1 - cos(angle)) - u.z * sin(angle), u.x * u.z * (1 - cos(angle)) + u.y * sin(angle), 0),
			Float4(u.y * u.x * (1 - cos(angle)) + u.z * sin(angle), cos(angle) + u.y * u.y * (1 - cos(angle)), u.y * u.z * (1 - cos(angle)) - u.x * sin(angle), 0),
			Float4(u.z * u.x * (1 - cos(angle)) - u.y * sin(angle), u.z * u.y * (1 - cos(angle)) + u.x * sin(angle), cos(angle) + u.z * u.z * (1 - cos(angle)), 0),
			Float4(0, 0, 0, 1));

		Vector originalTranslation = Vector(transformation[0][3], transformation[1][3], transformation[2][3]);
		this->translate(-originalTranslation);
		transformation = product(rotation, transformation);
		this->translate(originalTranslation);
	}

	void Instance::scale(float scale)
	{
		for(int i = 0; i < 3; ++i)
		{
			transformation[i][i] *= scale;
		}
	}
	void Instance::scale(const Vector& scale)
	{
		transformation[0][0] *= scale.x;
		transformation[1][1] *= scale.y;
		transformation[1][2] *= scale.z;
	}

	BBox Instance::getBounds() const
	{
		BBox originalBox = Content->getBounds();

		Point x1y1z1 = originalBox.minCorner;
		Point x2y2z2 = originalBox.maxCorner;

		float x1 = x1y1z1.x;
		float y1 = x1y1z1.y;
		float z1 = x1y1z1.z;

		float x2 = x2y2z2.x;
		float y2 = x2y2z2.y;
		float z2 = x2y2z2.z;

		Point x1y1z2 = Point(x1, y1, z2);

		Point x1y2z1 = Point(x1, y2, z1);
		Point x1y2z2 = Point(x1, y2, z2);
		
		Point x2y1z1 = Point(x2, y1, z1);
		Point x2y1z2 = Point(x2, y1, z2);

		Point x2y2z1 = Point(x2, y2, z1);
		
		Point p1 = transformation * x1y1z1;
		Point p2 = transformation * x1y1z2;
		Point p3 = transformation * x1y2z1;
		Point p4 = transformation * x1y2z2;

		Point p5 = transformation * x2y1z1;
		Point p6 = transformation * x2y1z2;
		Point p7 = transformation * x2y2z1;
		Point p8 = transformation * x2y2z2;

		Point newMinCorner = min(p1, min(p2, min(p3, min(p4, min(p5, min(p6, min(p7, p8)))))));
		Point newMaxCorner = max(p1, max(p2, max(p3, max(p4, max(p5, max(p6, max(p7, p8)))))));

		return BBox(newMinCorner, newMaxCorner);
	}

	Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const
	{
		//T T-1 = I
		Ray tempRay = ray;
		Matrix inverseTransform = transformation.invert();
		tempRay.o = inverseTransform * ray.o;
		tempRay.d = (inverseTransform  * ray.d).normalize();

		// Todo: Not sure about why the distance should be changed!
		float tempPreviousBestDistance = (inverseTransform * ray.getPoint(previousBestDistance) - tempRay.o).length();

		// ray intersection in object space
		Intersection intersection = Content->intersect(tempRay, tempPreviousBestDistance);
		if (intersection)
		{
			Point intersectedPoint = transformation * intersection.hitPoint();
			float distance = (intersectedPoint - ray.o).length();
			Intersection backTransformedIntersection = Intersection(distance, ray, intersection.solid, (inverseTransform.transpose() * intersection.normal()).normalize());
			return backTransformedIntersection;
		}
		return intersection;
	}

	void setMaterial(Material* m) 
	{
		NOT_IMPLEMENTED;
	}
	void setCoordMapper(CoordMapper* cm) 
	{
		NOT_IMPLEMENTED;
	}

}