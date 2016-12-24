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
		this->zenith = cross(thirdZ, this->azimuthRef).normalize();
	}
	Point SphericalCoordMapper::getCoords(const Intersection & hit) const
	{
		Point local = hit.local();
		Vector v = local - origin;
		v = Vector(dot(v, azimuthRef), dot(v, zenith), dot(v, thirdZ));
		float phi = atan2(v.y, v.x);
		float r = v.length();
		float theta = acos(v.z / r);
		return Point (phi / (2 * pi * aScale), theta / (pi * zScale), 0);
	}
}
