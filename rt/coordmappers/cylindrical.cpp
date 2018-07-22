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
		transformation = Matrix::system(polarAxis.normalize(), longitudinalAxis.normalize(), thirdZ).invert();
		Point nOrigin = Point(-origin.x, -origin.y, -origin.z);
		transformation = product(transformation.transpose(), translation(nOrigin));
	
	}
	Point CylindricalCoordMapper::getCoords(const Intersection & hit) const
	{
		Point translatedPoint = transformation * hit.local();
		float phi = atan2(translatedPoint.y,translatedPoint.x);
		return Point (phi / (2 * pi * pScale), translatedPoint.z / lScale, 0);
	}
}
