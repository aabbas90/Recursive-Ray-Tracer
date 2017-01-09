#include "bmap.h"

namespace rt
{
	BumpMapper::BumpMapper(Triangle * base, Texture * bumpmap, const Point & bv1, const Point & bv2, const Point & bv3, float vscale)
	{
		baseT = base;
		bMap = bumpmap;
		this->bv1 = bv1;
		this->bv2 = bv2;
		this->bv3 = bv3;
		vScale = vscale;
	}
	BBox BumpMapper::getBounds() const
	{
		return baseT->getBounds();
	}
	Intersection BumpMapper::intersect(const Ray & ray, float previousBestDistance) const
	{
		Intersection triangleInt = baseT->intersect(ray, previousBestDistance);
		if (triangleInt)
		{
			// TODO:
		}
		return triangleInt;
	}
	void BumpMapper::setMaterial(Material * m)
	{
		baseT->setMaterial(m);
	}
	void BumpMapper::setCoordMapper(CoordMapper * cm)
	{
		baseT->setCoordMapper(cm);
	}
}
