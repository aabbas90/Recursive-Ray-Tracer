#ifndef CG1RAYTRACER_MATERIALS_CAMERALCD_HEADER
#define CG1RAYTRACER_MATERIALS_CAMERALCD_HEADER

#include <rt/materials/material.h>
#include <core/point.h>

namespace rt {

	class CameraLCDmaterial : public Material {
	public:
		CameraLCDmaterial(
			const Point& center,
			const Point& leftUpCoord,
			const Vector& forward,
			const Vector& up,
			float verticalOpeningAngle,
			float horizonalOpeningAngle,
			float cameraSizeX,
			float cameraSizeY,
			float f);
		virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
		virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
		virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
		virtual Point getRayOrigin(Point& originalPoint) const;
		virtual Sampling useSampling() const { return Material::SAMPLING_ALL; }

	private:
		Point center;
		Point leftUpCoord;
		Vector forward;
		Vector up;
		Vector right;
		Vector spanningH, spanningV;
		float verticalOpeningAngle, horizonalOpeningAngle;
		float cameraSizeX, cameraSizeY;
		float f;
	};
}

#endif
