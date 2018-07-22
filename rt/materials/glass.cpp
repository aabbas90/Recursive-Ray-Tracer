#include "glass.h"
#include<core/random.h>
#include <math.h>

namespace rt
{
	GlassMaterial::GlassMaterial(float eta)
	{
		this->eta = eta;
	}
	RGBColor GlassMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
        return RGBColor(1, 1, 1); 
	}
	RGBColor GlassMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor(0, 0, 0);
	}
	SampleReflectance GlassMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		// adapted from: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
		Vector finalDirection;

		float cosThetaOut = dot(normal, -outDir);
		bool comingFromAir = cosThetaOut > 0 ? true : false;
		Vector currentNormal = normal;
		float currentEta = eta;

		if (!comingFromAir)
		{
			currentEta = 1 / eta;
			currentNormal = -1 * normal;
			cosThetaOut = -1 * cosThetaOut;
		}

		float randomN = random();

		//Ray gets reflected:
		if (randomN > 0.8)
		{
			finalDirection = (outDir + 2 * cosThetaOut * currentNormal).normalize();
		}

		// Ray get refracted:
		else
		{
			float theta1 = acos(cosThetaOut);
			float theta2 = asin(sin(theta1) / currentEta);
			Vector C = cos(theta1) * currentNormal;
			Vector M = (outDir + C) / sin(theta1);
			Vector A = sin(theta2) * M;
			Vector B = -cos(theta2) * currentNormal;
			finalDirection = (A + B).normalize();
		}		
		return SampleReflectance(finalDirection, RGBColor(1, 1, 1));
	}
	Point GlassMaterial::getRayOrigin(Point & originalPoint) const
	{
		return originalPoint;
	}
}
