//#ifndef CG1RAYTRACER_SOLIDS_cameraLCD_HEADER
//#define CG1RAYTRACER_SOLIDS_cameraLCD_HEADER
//
//#include <rt/solids/solid.h>
//#include <core/point.h>
//#include <rt/bbox.h>
//
//namespace rt {
//
//	class cameraLCD : public Solid {
//	public:
//		cameraLCD() {}
//		cameraLCD(const Point& p1, const Vector& span1, const Vector& span2, float f, float angleX, float angleY, CoordMapper* texMapper, Material* material);
//
//		virtual BBox getBounds() const;
//		virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
//		virtual Point sample() const;
//		virtual float getArea() const;
//		Ray getCameraRay(Intersection intersection);
//
//	private:
//		Point cameraCentre;
//		float angleX;
//		float angleY;
//		Point p1;
//		Vector spanH, spanV;
//		BBox box;
//	};
//
//}
//
//#endif
