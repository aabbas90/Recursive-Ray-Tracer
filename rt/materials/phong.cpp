#include <rt/materials/phong.h>
#include <rt/materials/material.h>
#include <math.h>
#include <core/scalar.h>

namespace rt
{
    PhongMaterial::PhongMaterial(Texture* specular, float exponent)
    {
        this->specular = specular;
        this->exponent = exponent;
    }
    RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
        //https://www.cg.tuwien.ac.at/courses/Rendering/VU.SS2016.html
        //I = ks(V.R)^n
        //https://en.wikipedia.org/wiki/Phong_reflection_model
        //R = 2(L.N)N - L
        Vector R = 2 * dot(inDir, normal) * normal - inDir;
         //TODO what if dot product is -ve -reflection or refraction
        //return specular->getColor(texPoint) * ((exponent+2)/(2*pi))* powf(dot(outDir, R), exponent);
        return specular->getColor(texPoint) * powf(dot(outDir, R), exponent);
    }
    RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {


        //No emission
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        return SampleReflectance();     
    }
    Material::Sampling PhongMaterial::useSampling() const
    {
        return Material::Sampling::SAMPLING_NOT_NEEDED;
    }
}