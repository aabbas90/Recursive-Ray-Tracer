#include "spherical.h"
#include <core/assert.h>
#include <rt/intersection.h>

namespace rt
{
	SphericalCoordMapper::SphericalCoordMapper()
	{}
	SphericalCoordMapper::SphericalCoordMapper(const Point & origin, const Vector & zenith, const Vector & azimuthRef)
	:origin(origin), zenith(zenith), azimuthRef(azimuthRef)
	{
		zScale = zenith.length();
		aScale = azimuthRef.length();
		thirdZ = cross(this->azimuthRef, this->zenith).normalize();
		transformation = Matrix::system(zenith.normalize(), azimuthRef.normalize(), thirdZ).invert();
		transformation = product(transformation.transpose(), translation(Point(-origin.x, -origin.y, -origin.z)));
	}
	Point SphericalCoordMapper::getCoords(const Intersection & hit) const
	{
		Point translatedPoint = transformation * hit.local();
		float phi = atan2(translatedPoint.y, translatedPoint.x);
		float r = sqrt(translatedPoint.x * translatedPoint.x + translatedPoint.y * translatedPoint.y+ translatedPoint.z * translatedPoint.z);
		float theta = acos(translatedPoint.z / r);
		return Point (phi / (2 * pi * aScale), theta / (pi * zScale), 0);
	}
}
