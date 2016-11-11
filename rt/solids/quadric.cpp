#include <rt/solids/quadric.h>
#include <core/assert.h>
#include <math.h>

using namespace rt;

//Reference : https://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter4.htm

Quadric::Quadric(const float a, 
                const float b, 
                const float c, 
                const float d, 
                const float e, 
                const float f, 
                const float g, 
                const float h, 
                const float i, 
                const float j, 
                CoordMapper* texMapper, Material* material)
                : a(a), b(b), c(c), d(d), e(e),
                  f(f), g(g), h(h), i(i), j(j)
{
    this->texMapper = texMapper;
	this->material = material;
}

BBox Quadric::getBounds() const
{
    NOT_IMPLEMENTED;
}
Intersection Quadric::intersect(const Ray& ray, float previousBestDistance) const 
{
    float t2_a = a * ray.d.x * ray.d.x + b * ray.d.y * ray.d.y + c * ray.d.z * ray.d.z 
                + d * ray.d.x * ray.d.y + e * ray.d.x * ray.d.z + f * ray.d.y * ray.d.z;
    float t_b = 2.0 * a * ray.d.x * ray.o.x + 2.0 * b * ray.d.y * ray.o.y + 2.0 * c * ray.d.z * ray.o.z 
                + d * (ray.d.y * ray.o.x + ray.d.x * ray.o.y) 
                + e * (ray.d.x * ray.o.z + ray.d.z * ray.o.x) 
                + f * (ray.d.y * ray.o.z + ray.d.z * ray.o.y)
                + g * ray.d.x + h * ray.d.y + i * ray.d.z;
    float constant_c = a * ray.o.x * ray.o.x + b * ray.o.y * ray.o.y + c * ray.o.z * ray.o.z 
                    + d * ray.o.x * ray.o.y + e * ray.o.x * ray.o.z + f * ray.o.y * ray.o.z 
                    + g * ray.o.x + h * ray.o.y + i * ray.o.z + j;

    float D = t_b - 4.0 * t2_a * constant_c;
    float t = 0;

    if (D < 0) // Ray doesn't intersect the Quadric
    {
        return Intersection();
    }
    else if (D == 0) // Ray is tangent to Quadric
    {
        float t  = - t_b / (2.0 * t2_a);
    }
    else // if(D > 0) Ray intersects at two points
    {
        float t1 = (- t_b - sqrtf(D)) / (2.0 * t2_a); 
        if(t1 > 0)  
        {
            if(t1 > previousBestDistance) 
                return Intersection();
            else  
                t = t1;       
        }
        else //t1 < 0
        {
            float t2 = (- t_b + sqrtf(D)) / (2.0 * t2_a);
            if(t2 > previousBestDistance) 
                return Intersection();
            else  
                t = t2;
        }
    }
    Point intersectionPoint = ray.getPoint(t);
    float delX = 2.0 * a * intersectionPoint.x + d * intersectionPoint.y + e * intersectionPoint.z + g;
    float delY = 2.0 * b * intersectionPoint.y + d * intersectionPoint.x + f * intersectionPoint.z + h;
    float delZ = 2.0 * c * intersectionPoint.z + e * intersectionPoint.x + f * intersectionPoint.y + i;
    Vector normal = Vector(delX, delY, delZ).normalize();
    return Intersection(t, ray, this, normal);

}
Point Quadric::sample() const
{
    NOT_IMPLEMENTED;
}
float Quadric::getArea() const
{
    NOT_IMPLEMENTED;
}