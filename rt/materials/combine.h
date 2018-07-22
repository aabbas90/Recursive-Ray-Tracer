#ifndef CG1RAYTRACER_MATERIALS_COMBINE_HEADER
#define CG1RAYTRACER_MATERIALS_COMBINE_HEADER

#include <rt/materials/material.h>
#include <vector>

namespace rt {

class CombineMaterial : public Material {
public:
    CombineMaterial(){}
    void add(Material* material, float weight);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
	virtual Point getRayOrigin(Point& originalPoint) const;
	Sampling sampling = Material::SAMPLING_NOT_NEEDED;

private:
    std::vector<std::pair<Material*, float> > materials;
};
    int getSamplingPriority(Material::Sampling samplingType);
}

#endif
