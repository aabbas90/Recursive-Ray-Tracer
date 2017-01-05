#include "glass.h"
#include<core/random.h>

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
		Vector finalDirection;

		float cosThetaOut = dot(normal, -outDir);
		bool comingFromAir = cosThetaOut > 0 ? true : false;
		float randomN = random();

		//Ray gets reflected:
		if (randomN > 0.5)
		{
			finalDirection = (outDir + 2 * cosThetaOut * normal).normalize();
		}

		// Ray get refracted:
		else
		{
			float currentEta = eta;
			if (!comingFromAir)
				currentEta = 1 / eta;

			float c2 = sqrt(1 - (1 / eta) * (1 / eta) * (1 - cosThetaOut * cosThetaOut));
			finalDirection = -((currentEta * (-outDir) + (currentEta  * cosThetaOut - c2) * normal).normalize());
		}
		return SampleReflectance(finalDirection, RGBColor(1, 1, 1));
	}
}
