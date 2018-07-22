#include <rt/materials/flatmaterial.h>
#include <core/color.h>


namespace rt
{
	FlatMaterial::FlatMaterial(Texture * texture)
	{
		this->texture = texture;
	}
	RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		//no reflectance
		return RGBColor::black();
	}
	
    RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return texture->getColor(texPoint);
	}

    SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return SampleReflectance();
	}

	Point FlatMaterial::getRayOrigin(Point & originalPoint) const
	{
		return originalPoint;
	}

}
