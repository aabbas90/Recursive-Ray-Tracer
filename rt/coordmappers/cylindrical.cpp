#include "cylindrical.h"
#include <core/assert.h>
#include <rt/intersection.h>


namespace rt
{
	CylindricalCoordMapper::CylindricalCoordMapper(const Point & origin, const Vector & longitudinalAxis, const Vector & polarAxis)
	: origin(origin), longitudinalAxis(longitudinalAxis), polarAxis(polarAxis)
	{
		lScale = longitudinalAxis.length();
		pScale = polarAxis.length();
		thirdZ = cross(this->polarAxis, this->longitudinalAxis).normalize();
		transformation = Matrix::system(longitudinalAxis.normalize(), polarAxis.normalize(), thirdZ).invert();
		transformation = product(transformation, translation(Point(-origin.x, -origin.y, -origin.z)));	
	}
	Point CylindricalCoordMapper::getCoords(const Intersection & hit) const
	{
		Point translatedPoint = transformation * hit.local();
		float x = translatedPoint.x;
		float y = translatedPoint.y;
		float phi = atan2(y,x);
		return Point (phi / (2 * pi * pScale), translatedPoint.z / lScale, 0);
	}
}
