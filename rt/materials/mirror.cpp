#include <rt/materials/mirror.h>

namespace rt
{
    // for Electric Conductors (e.g. Metals)
    MirrorMaterial(float eta, float kappa)
    {
        this->eta = eta;
        this->kappa = kappa;
    }
    RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
        cosTheta = dot(normal.normalize(), inDir.normalize());
        rParallelSq = ((eta*eta + kappa*kappa) * cosTheta*cosTheta - 2*eta*cosTheta + 1 ) / ((eta*eta + kappa*kappa) * cosTheta*cosTheta + 2*eta*cosTheta + 1 );
        rPerpendicularSq = ((eta*eta + kappa*kappa) - 2*eta*cosTheta + cosTheta*cosTheta) / ((eta*eta + kappa*kappa) + 2*eta*cosTheta + cosTheta*cosTheta);
        Fr = 0.5f * (rParallelSq + rPerpendicularSq);
        return RGBColor(Fr, Fr, Fr); //grayscale
    }
    RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        //no emission
        return RGBColor (0.0f, 0.0f, 0.0f);
    }
    SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        //TODO
        NOT_IMPLEMENTED;
    }
    Sampling MirrorMaterial::useSampling() const
    {
        NOT_IMPLEMENTED;
    }
}