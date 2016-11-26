#include <rt/primmod/instance.h>
#include <rt/bbox.h>
#include <core/assert.h>


namespace rt {

	Instance::Instance(Primitive* content)
	{
		content = this;
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
		Vector originalTranslation = Vector(transformation[0][3], transformation[1][3], transformation[2][3]);
		Vector sDash;
		if (fabs(axis.x) < fabs(axis.y))
		{
			if (fabs(axis.x) < fabs(axis.z))
			{
				sDash = Vector(0, -axis.z, axis.y);
			}
			else
			{
				sDash = Vector(-axis.y, axis.x, 0);
			}
		}
		else
		{
			if (fabs(axis.y) < fabs(axis.z))
			{
				sDash = Vector(-axis.z, 0, axis.x);
			}

			else
			{
				sDash = Vector(-axis.y, axis.x, 0);
			}
		}
		Vector s = sDash.normalize();
		Vector t = cross(axis, s);
		Matrix M = Matrix(Float4(axis.x, s.x, t.x, 0),
						  Float4(axis.y, s.y, t.y, 0),
						  Float4(axis.z, s.z, t.z, 0),
						  Float4(0, 0, 0, 1));

		Matrix Rx = Matrix(Float4(1, 0, 0, 0),
			Float4(0, cos(angle), -sin(angle), 0),
			Float4(0, sin(angle), cos(angle), 0),
			Float4(0, 0, 0, 1));

		Matrix FullR = product(M, product(Rx, M.transpose()));
		this->translate(-originalTranslation);
		transformation = product(FullR, transformation);
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
		// Todo: Transform all six corners of original bbox, and then recreate a transformed bbox with component-wise min and max coordinates of the transformed points:
		return getBounds(); ////TODO: transform?
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
		Intersection intersection = intersect(tempRay, tempPreviousBestDistance);
		if (intersection)
		{
			// Transform intersection point to world space
			Point intersectedPoint = transformation * intersection.hitPoint();

			//  Scale intersection distance in world space by normalization factor
			Vector normal = (inverseTransform.transpose() * intersection.normal()).normalize();
			//Todo previousbestdistance?
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