#include "dummy.h"
#include <rt/materials/material.h>
#include <core/assert.h>
#include <cmath>

namespace rt
{	
	DummyMaterial::DummyMaterial()
	{
	}
	RGBColor DummyMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		float incomingFactor = std::abs(dot(normal.normalize(), inDir.normalize()));

		return RGBColor(incomingFactor, incomingFactor, incomingFactor);
	}
	RGBColor DummyMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor();
	}
	SampleReflectance DummyMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		NOT_IMPLEMENTED;
	}
	Point DummyMaterial::getRayOrigin(Point& originalPoint) const
	{
		return originalPoint;
	}
}
