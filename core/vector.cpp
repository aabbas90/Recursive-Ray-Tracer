#include "vector.h"
#include "point.h"
#include <algorithm>
#include <math.h>	
#include "float4.h"
#include <core/assert.h>

namespace rt
{
	Vector Vector::operator+(const Vector & b) const
	{
		return Vector(this->x + b.x, this->y + b.y, this->z + b.z);
	}

	Vector Vector::operator-(const Vector & b) const
	{
		return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
	}

	Vector Vector::operator-() const
	{
		return Vector(-this->x, -this->y, -this->z);
	}

	float Vector::length() const
	{
		return sqrtf(this->lensqr());
	}

	float Vector::lensqr() const
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	bool Vector::operator==(const Vector & b) const
	{
		return (this->x == b.x && this->y == b.y && this->z == b.z) ? 1 : 0;
	}

	bool Vector::operator!=(const Vector & b) const
	{
		return (this->x != b.x || this->y != b.y || this->z != b.z) ? 1 : 0;
	}

	Vector Vector::normalize() const
	{
		float length = this->length();
		return Vector(this->x / length, this->y / length, this->z / length);
	}

	Point Vector::ToPoint()
	{
		return Point(this->x, this->y, this->z);
	}

	Vector operator*(float scalar, const Vector & b)
	{
		return Vector(b.x * scalar, b.y * scalar, b.z * scalar);
	}

	Vector operator*(const Vector & a, float scalar)
	{
		return scalar * a;
	}

	Vector operator/(const Vector & a, float scalar)
	{
		return (1 / scalar) * a;
	}

	Vector cross(const Vector & a, const Vector & b)
	{
		return Vector(a.y * b.z - a.z * b.y,
					  a.z * b.x - a.x * b.z,
					  a.x * b.y - a.y * b.x);
	}

	float dot(const Vector & a, const Vector & b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Vector min(const Vector & a, const Vector & b)
	{
		return Vector(a.x < b.x ? a.x : b.x,
					  a.y < b.y ? a.y : b.y,
					  a.z < b.z ? a.z : b.z);
	}

	Vector max(const Vector & a, const Vector & b)
	{
		return Vector(a.x > b.x ? a.x : b.x,
					  a.y > b.y ? a.y : b.y,
					  a.z > b.z ? a.z : b.z);
	}

	Point operator+(const Point & a, const Vector & b)
	{
		return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	Point operator+(const Vector & a, const Point & b)
	{
		return b + a;
	}

	Point operator-(const Point & a, const Vector & b)
	{
		return Point(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	//TODO check for w
	Point operator*(const Float4 & scale, const Point & p)
	{
		return Point(scale.x * p.x, scale.y * p.y, scale.z * p.z);
	}

	std::ostream& operator<<(std::ostream& os, const Vector& v)
	{
	    os << "VECTOR x:" << v.x << " y:" << v.y << " z:" << v.z  << " length: " << v.length();
	    return os;
	}

	Vector::Vector(const Float4 & f4)
	{
		this->x = f4.x;
		this->y = f4.y;
		this->z = f4.z;
	}
}
