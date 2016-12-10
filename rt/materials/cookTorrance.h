#ifndef CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER
#define CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

class CookTorranceMaterial : public Material {
public:
    CookTorranceMaterial(Texture* texture, float diffusedFactor,  float refractiveIndex, float roughnessM);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
private:
    Texture* texture;
    float diffusedCoeff;
    float fresnelCoeff;
    float roughnessM;
};

}

#endif
