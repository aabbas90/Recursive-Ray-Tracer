#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <core/scalar.h>

namespace rt
{
    LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
    {
        this->emission = emission;
        this->diffuse = diffuse;
    }
    RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
        // f(ωi, ωo) = R / pi
        // kd (Li . N) where kd is diffuse coefficient
        // TODO: insure getColor returns value between [0,1], if not, clamp
        return (diffuse->getColor(texPoint) * dot(inDir, normal)) / pi;
    }
    RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        return emission->getColor(texPoint);
    }
    SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {  
        return SampleReflectance();
    }
    Material::Sampling LambertianMaterial::useSampling() const
    {
        return Material::Sampling::SAMPLING_NOT_NEEDED;
    }
	Point LambertianMaterial::getRayOrigin(Point & originalPoint) const
	{
		return originalPoint;
	}
}