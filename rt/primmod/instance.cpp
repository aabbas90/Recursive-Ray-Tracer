#include <rt/primmod/instance.h>

namespace rt {

    Instance(Primitive* content)
    {
        this->content = content;
        transformation = Matrix::identity();
    }   
    Primitive* content()
    {
        return content;
    }
    void reset()
    {
        transformation = Matrix::identity();
    }
    void translate(const Vector& t)
    {
        transformation[0][3] += t.x;
        transformation[1][3] += t.y;
        transformation[2][3] += t.z;
    }
    void rotate(const Vector& axis, float angle)
    {
         
    }
    void scale(float scale)
    {
        for(int i = 0; i < 3; ++i)
        {
            transformation[i][i] *= scale;
        }
    }
    void scale(const Vector& scale)
    {
        transformation[0][0] *= scale.x;
        transformation[1][1] *= scale.y;
        transformation[1][2] *= scale.z;
    }
    Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const
    {

    }

}