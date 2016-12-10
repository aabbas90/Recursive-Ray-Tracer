#include <rt/materials/mirror.h>
#include <core/assert.h>

namespace rt
{
    // for Electric Conductors (e.g. Metals)
    MirrorMaterial::MirrorMaterial(float eta, float kappa)
    {
        this->eta = eta;
        this->kappa = kappa;
    }
    RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
        float cosTheta = dot(normal.normalize(), inDir.normalize());
        float rParallelSq = ((eta*eta + kappa*kappa) * cosTheta*cosTheta - 2*eta*cosTheta + 1 ) / ((eta*eta + kappa*kappa) * cosTheta*cosTheta + 2*eta*cosTheta + 1 );
        float rPerpendicularSq = ((eta*eta + kappa*kappa) - 2*eta*cosTheta + cosTheta*cosTheta) / ((eta*eta + kappa*kappa) + 2*eta*cosTheta + cosTheta*cosTheta);
        float Fr = 0.5f * (rParallelSq + rPerpendicularSq);
        return RGBColor(Fr, Fr, Fr); //grayscale
    }
    RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        //no emission
        return RGBColor (0.0f, 0.0f, 0.0f);
    }
    SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        //R(W)=2(W•N)N-W
        //TODO check if negative of this 
        Vector dir = 2 * dot(outDir, normal) * normal - outDir;
	    RGBColor color = getReflectance(texPoint, normal, outDir, dir);
	    return SampleReflectance(dir, color);
    }
    Material::Sampling MirrorMaterial::useSampling() const
    {
        return Material::Sampling::SAMPLING_ALL;
    }
}