#include "cameraLCDMaterial.h"

namespace rt
{

	CameraLCDmaterial::CameraLCDmaterial(const Point & center, const Point& leftUpCoord, const Vector & forward, const Vector & up, float verticalOpeningAngle, float horizonalOpeningAngle, float cameraSizeX, float cameraSizeY, float f)
	{
		this->center = center;
		this->leftUpCoord = leftUpCoord;
		this->right = cross(forward, up).normalize();
		this->up = cross(right, forward).normalize(); // Ensuring that all three vectors are perpendicular
		this->cameraSizeX = cameraSizeX;
		this->cameraSizeY = cameraSizeY;
		spanningH = this->right * tan(horizonalOpeningAngle / 2.0f);
		spanningV = this->up * tan(verticalOpeningAngle / 2.0f);
		this->f = f;
	}

	RGBColor CameraLCDmaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		return RGBColor(1, 1, 1);
	}

	RGBColor CameraLCDmaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor(0, 0, 0);
	}

	SampleReflectance CameraLCDmaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		float dotP = dot(normal, outDir);
		if (dotP > 0)
			return SampleReflectance(normal, RGBColor(0, 0, 0));

		Vector displacementVector = texPoint - center;
		Vector forwardVector = cross(spanningH, spanningV).normalize();

		float xDot = 2 * dot(displacementVector, right) / cameraSizeX;
		float yDot = 2 * dot(displacementVector, up) / cameraSizeY;

		Vector x = xDot * spanningH;
		Vector y = yDot * spanningV;

		float fDot = dot(forwardVector, displacementVector);

		Vector newDirection = -forwardVector + x + y;
		return SampleReflectance(newDirection.normalize(), RGBColor(1, 1, 1));
	}

	Point CameraLCDmaterial::getRayOrigin(Point & originalPoint) const
	{
		return originalPoint;
	}
}