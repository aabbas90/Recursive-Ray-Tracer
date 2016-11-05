#include "triangle.h"

namespace rt
{
Triangle::Triangle(Point vertices[3], CoordMapper * texMapper, Material * material)
{
	this->v1 = vertices[0];
	this->v2 = vertices[1];
	this->v3 = vertices[2];
	this->texMapper = texMapper;
	this->material = material;
}

Triangle::Triangle(const Point & v1, const Point & v2, const Point & v3, CoordMapper * texMapper, Material * material)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->texMapper = texMapper;
	this->material = material;
}
