#include "vector.h"
#include "point.h"
#include <algorithm>

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
		return std::sqrtf(this->lensqr());
	}

	float Vector::lensqr() const
	{
		return this->x * this->x + this->y + this->y + this->z + this->z;
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

	// Incomplete:
	Point operator*(const Float4 & scale, const Point & p)
	{
		return Point();
	}
}
