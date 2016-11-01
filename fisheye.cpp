#include "fisheye.h"
#include <math.h>

using namespace rt;

FishEyeCamera::FishEyeCamera(const Point & center, const Vector & forward, const Vector & up, float viewingAngleX, float viewingAngleY) : 
	center(center), forward(forward), up(up), viewingAngleX(viewingAngleX), viewingAngleY(viewingAngleY)
{
	this->right = cross(up, forward).normalize();
	this->up = cross(forward, right).normalize(); // Ensuring that all three vectors are perpendicular
}

Ray FishEyeCamera::getPrimaryRay(float x, float y) const
{
	Vector xVector= x * right;
	Vector yVector = y * up;
	Vector xyVector = xVector + yVector;
	
	if (xyVector.lensqr() > 1)
		return Ray(Point(0,0,0), Vector(0,0,0));

	float zCoordinate =  sqrtf(1 - xyVector.x * xyVector.x - xyVector.y * xyVector.y);
	return Ray(center, Vector(xyVector.x, xyVector.y, zCoordinate).normalize());
}
