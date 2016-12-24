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
		this->longitudinalAxis = cross(thirdZ, this->polarAxis).normalize();
	}
	Point CylindricalCoordMapper::getCoords(const Intersection & hit) const
	{
		Point local = hit.local();
		Vector v = local - origin;
		v = Vector(dot(v, polarAxis), dot(v, longitudinalAxis), dot(v, thirdZ));
		float phi = atan2(v.y, v.x);
		return Point (phi / (2 * pi * pScale), v.z / lScale, 0);

	}
}
