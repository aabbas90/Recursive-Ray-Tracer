#include "fuzzymirror.h"
#include <core/scalar.h>
#include <core/random.h>

namespace rt
{
	FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
	{
		this->eta = eta;
		this->kappa = kappa;
		this->fuzzyangle = fuzzyangle;
	}

	RGBColor FuzzyMirrorMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		float cosTheta = dot(normal.normalize(), inDir.normalize());
		float rParallelSq = ((eta*eta + kappa*kappa) * cosTheta*cosTheta - 2 * eta*cosTheta + 1) / ((eta*eta + kappa*kappa) * cosTheta*cosTheta + 2 * eta*cosTheta + 1);
		float rPerpendicularSq = ((eta*eta + kappa*kappa) - 2 * eta*cosTheta + cosTheta*cosTheta) / ((eta*eta + kappa*kappa) + 2 * eta*cosTheta + cosTheta*cosTheta);
		float Fr = 0.5f * (rParallelSq + rPerpendicularSq);
		return RGBColor(Fr, Fr, Fr); //grayscale
	}

	RGBColor FuzzyMirrorMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor(0, 0, 0);
	}

	SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		Vector xSpanningVector = Vector(1, 0, 0);
		Vector ySpanningVector = Vector(0, 1, 0);
		if (std::abs(dot(xSpanningVector, normal)) != 1)
		{
			ySpanningVector = cross(normal, xSpanningVector).normalize();
			xSpanningVector = cross(ySpanningVector, normal).normalize();
		}
		else
		{
			xSpanningVector = cross(ySpanningVector, normal).normalize();
			ySpanningVector = cross(normal, xSpanningVector).normalize();
		}


		float theta = random() * 2 * pi;
		float maximumRadius = tanf(fuzzyangle);
		float r = random() * maximumRadius;
		float x_polar = std::cos(theta) * r;
		float y_polar = std::sin(theta) * r;

		float dotP = dot(outDir, normal);
		Vector dir = (outDir - 2 * dotP * normal + xSpanningVector * x_polar + ySpanningVector * y_polar).normalize();
		RGBColor color = getReflectance(texPoint, normal, outDir, dir);
		return SampleReflectance(dir, color);
	}

	Point FuzzyMirrorMaterial::getRayOrigin(Point & originalPoint) const
	{
		return originalPoint;
	}

}
