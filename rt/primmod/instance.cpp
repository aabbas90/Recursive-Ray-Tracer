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
		Vector originalTranslation = Vector(transformation[0][3], transformation[1][3], transformation[2][3]);
		Vector sDash;
		Vector r = axis.normalize();
		if (fabs(r.x) < fabs(r.y))
		{
			if (fabs(r.x) < fabs(r.z))
			{
				sDash = Vector(0, -r.z, r.y);
			}
			else
			{
				sDash = Vector(-r.y, r.x, 0);
			}
		}
		else
		{
			if (fabs(r.y) < fabs(r.z))
			{
				sDash = Vector(-r.z, 0, r.x);
			}

			else
			{
				sDash = Vector(-r.y, r.x, 0);
			}
		}
		Vector s = sDash.normalize();
		Vector t = cross(r, s).normalize();
		Matrix M = Matrix(Float4(r.x, s.x, t.x, 0),
						  Float4(r.y, s.y, t.y, 0),
						  Float4(r.z, s.z, t.z, 0),
						  Float4(0, 0, 0, 1));

		Matrix Rx = Matrix(Float4(1, 0, 0, 0),
			Float4(0, cos(angle), -sin(angle), 0),
			Float4(0, sin(angle), cos(angle), 0),
			Float4(0, 0, 0, 1));

		transformation = product(M.transpose(), transformation);
		transformation = product(Rx, transformation);
		transformation = product(M, transformation);

		//Matrix FullR = product(M, product(Rx, M.transpose()));
		//this->translate(-originalTranslation);
		//transformation = product(FullR, transformation);
		//this->translate(originalTranslation);
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
		BBox bbox = this->Content->getBounds();
		return BBox(transformation * bbox.minCorner, transformation * bbox.maxCorner);
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