#include <rt/primmod/bmap.h>
#include <rt/coordmappers/tmapper.h>
#include <rt/coordmappers/world.h>
#include <core/float4.h>


namespace rt
{
	BumpMapper::BumpMapper(Triangle * base, Texture * bumpmap, const Point & bv1, const Point & bv2, const Point & bv3, float vscale)
	{
		baseT = base;
		bMap = bumpmap;
		vScale = vscale;
		baseT->texMapper = new TriangleMapper(bv1, bv2, bv3);
		this->bv1 = bv1;
		this->bv2 = bv2;
		this->bv3 = bv3;

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
			Point texturePoint = baseT->texMapper->getCoords(triangleInt);
			// std::cout << texturePoint << std::endl;
			// gradient at the given texture coordinates
			float DX = bMap->getColorDX(texturePoint).grayscale();	
			float DY = bMap->getColorDY(texturePoint).grayscale();
			
			Vector origNormal = triangleInt.normal().normalize();
			Vector xSpanningVector = Vector(1, 0, 0);
			Vector ySpanningVector = Vector(0, 1, 0);
			if (std::abs(dot(xSpanningVector, origNormal)) != 1)
			{
				ySpanningVector = cross(origNormal, xSpanningVector).normalize();
				xSpanningVector = cross(ySpanningVector, origNormal).normalize();
			}
			else
			{
				xSpanningVector = cross(ySpanningVector, origNormal).normalize();
				ySpanningVector = cross(origNormal, xSpanningVector).normalize();
			}

			//perturb the normal in world space
			//JUGAAD :/
			// Vector newNormal = Vector(DX * triangleInt.normal().x * 100.0f, DY * triangleInt.normal().y * 100.0f, triangleInt.normal().z * 100.0f);
			Vector newNormal = (origNormal + DX * cross(origNormal, xSpanningVector) + DY * cross(origNormal, ySpanningVector)).normalize();
			// std::cout << triangleInt.normal() << std::endl;
			// std::cout << newNormal << std::endl;
			// std::cout << std::endl;
			triangleInt.setNormal(newNormal);	
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
