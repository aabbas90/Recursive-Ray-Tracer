#ifndef CG1RAYTRACER_VECTOR_HEADER
#define CG1RAYTRACER_VECTOR_HEADER

#include <core/macros.h>
#include <iostream>

namespace rt {

class Point;
class Float4;

class ALIGN(16) Vector {
public:
	float x, y, z;

	Vector() {}
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}
	explicit Vector(const Float4& f4);

	static Vector rep(float v) { return Vector(v,v,v); }

	Vector operator+(const Vector& b) const;
	Vector operator-(const Vector& b) const;

	Vector normalize() const;

	
	Vector operator-() const;

	float lensqr() const;
	float length() const;

	bool operator==(const Vector& b) const;
	bool operator!=(const Vector& b) const;
	Point ToPoint();
};

Vector operator*(float scalar, const Vector& b);
Vector operator*(const Vector& a, float scalar);
Vector operator/(const Vector& a, float scalar);
Vector cross(const Vector& a, const Vector& b);
float dot(const Vector& a, const Vector& b);

Vector min(const Vector& a, const Vector& b);
Vector max(const Vector& a, const Vector& b);

Point operator+(const Point& a, const Vector& b);
Point operator+(const Vector& a, const Point& b);
Point operator-(const Point& a, const Vector& b);
Point operator*(const Float4& scale, const Point& p);
std::ostream& operator<<(std::ostream& os, const Vector& v);

}

#endif
