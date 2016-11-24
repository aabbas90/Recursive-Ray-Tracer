#ifndef CG1RAYTRACER_POINT_HEADER
#define CG1RAYTRACER_POINT_HEADER

#include <core/macros.h>
#include <iostream>
#include <core/float4.h>


namespace rt {

class Vector;

class ALIGN(16) Point {
public:
	float x, y, z;

	Point() {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	explicit Point(const Float4& f4);

	static Point rep(float v) { return Point(v,v,v); }

	Vector operator-(const Point& b) const;
	Point operator+(const Point & b) const;

	bool operator==(const Point& b) const;
	bool operator!=(const Point& b) const;

};

Point operator*(float scalar, const Point& b);
Point operator*(const Point& a, float scalar);

Point min(const Point& a, const Point& b);
Point max(const Point& a, const Point& b);
std::ostream& operator<<(std::ostream& os, const Point& pt);

}

#endif
