#include <rt/primmod/instance.h>
#include <rt/bbox.h>
#include <core/assert.h>


namespace rt {

    Instance::Instance(Primitive* content)
    {
        this->primitive = content;
        transformation = Matrix::identity();
    }   
    Primitive* Instance::content()
    {
        return primitive;
    }
    void Instance::reset()
    {
        transformation = Matrix::identity();
    }
    void Instance::translate(const Vector& t)
    {
        transformation[0][3] += t.x;
        transformation[1][3] += t.y;
        transformation[2][3] += t.z;
    }
    void Instance::rotate(const Vector& axis, float angle)
    {
         
    }
    void Instance::scale(float scale)
    {
        for(int i = 0; i < 3; ++i)
        {
            transformation[i][i] *= scale;
        }
    }
    void Instance::scale(const Vector& scale)
    {
        transformation[0][0] *= scale.x;
        transformation[1][1] *= scale.y;
        transformation[1][2] *= scale.z;
    }
    BBox Instance::getBounds() const
    {
        return primitive->getBounds(); //TODO: transform?
    }
    Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const
    {
        //T T-1 = I
        Ray tempRay = ray;
        tempRay.o = transformation.invert() * ray.o;
        tempRay.d = transformation.invert() * ray.d;
        // ray intersection in object space
        Intersection intersection = primitive->intersect(tempRay, previousBestDistance);
        if(intersection)
        {
            // Transform intersection point to world space
            Point intersectedPoint = transformation * intersection.hitPoint();
            //  Scale intersection distance in world space by normalization factor
            Vector normal = (transformation.invert().transpose() * intersection.normal()).normalize();
            //Todo previousbestdistance?
        }
        return intersection;
    }

    void setMaterial(Material* m) 
    {
        NOT_IMPLEMENTED;
    }
    void setCoordMapper(CoordMapper* cm) 
    {
        NOT_IMPLEMENTED;
    }

}