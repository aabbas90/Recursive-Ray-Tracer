
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/groups/simplegroup.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/solids/triangle.h>
#include <rt/solids/striangle.h>

using namespace rt;

namespace {

    void makeTesselatedSphere(Group*scene, const Point& center, float radius, int vtesselCount, int htesselCount, CoordMapper* texMapper, Material* material);
    void makeTesselatedSmoothSphere(Group*scene, const Point& center, float radius, int vtesselCount, int htesselCount, CoordMapper* texMapper, Material* material);

}

void renderTesselatedSphere(float scale, const char* filename, bool smooth) {
    Image img(400, 400);
    World world;
    SimpleGroup scene;
    world.scene = &scene;

    PerspectiveCamera cam(Point(278*scale, 273*scale, -800*scale), Vector(0, 0.5f, 1), Vector(0.1f, 1, 0), 0.686f, 0.686f);

    if (smooth)
        makeTesselatedSmoothSphere(&scene, Point(300.f,720.f,25.f)*scale, 200.f*scale, 8, 16, nullptr, nullptr);
    else
        makeTesselatedSphere(&scene, Point(300.f,720.f,25.f)*scale, 200.f*scale, 8, 16, nullptr, nullptr);

    RayCastingIntegrator integrator(&world);

    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG(filename);
}

void a_smooth() {
    renderTesselatedSphere(0.01f, "smooth-1.png", false);
    renderTesselatedSphere(0.01f, "smooth-2.png", true);
}





namespace {

    void makeTesselatedSphere(Group*scene, const Point& center, float radius, int vtesselCount, int htesselCount, CoordMapper* texMapper, Material* material) {
        float vangleStep = pi / vtesselCount;
        float hangleStep = (2*pi) / htesselCount;

        //top and bottom cone
        {
            Point top = center + Vector(0,0,radius);
            Point bottom = center - Vector(0,0,radius);

            float z = std::cos(vangleStep)*radius;
            float r = std::sin(vangleStep)*radius;
            for (int i=0; i<htesselCount; ++i) {
                Point tleft = center + Vector(
                    std::sin(i*hangleStep)*r,
                    std::cos(i*hangleStep)*r,
                    z);
                Point tright = center + Vector(
                    std::sin((i+1)*hangleStep)*r,
                    std::cos((i+1)*hangleStep)*r,
                    z);
                scene->add(new Triangle(top,tleft,tright,texMapper,material));
                Point bleft = center + Vector(
                    std::sin(i*hangleStep)*r,
                    std::cos(i*hangleStep)*r,
                    -z);
                Point bright = center + Vector(
                    std::sin((i+1)*hangleStep)*r,
                    std::cos((i+1)*hangleStep)*r,
                    -z);
                scene->add(new Triangle(bottom,bleft,bright,texMapper,material));
            }
        }

        //between top and bottom cones
        for (int y=1; y<vtesselCount-1; ++y) {
            float topz = std::cos(vangleStep*y)*radius;
            float bottomz = std::cos(vangleStep*(y+1))*radius;
            float topr = std::sin(vangleStep*y)*radius;
            float bottomr = std::sin(vangleStep*(y+1))*radius;
            for (int x=0; x<htesselCount; ++x) {
                Point tleft = center + Vector(
                    std::sin(x*hangleStep)*topr,
                    std::cos(x*hangleStep)*topr,
                    topz);
                Point tright = center + Vector(
                    std::sin((x+1)*hangleStep)*topr,
                    std::cos((x+1)*hangleStep)*topr,
                    topz);
                Point bleft = center + Vector(
                    std::sin(x*hangleStep)*bottomr,
                    std::cos(x*hangleStep)*bottomr,
                    bottomz);
                Point bright = center + Vector(
                    std::sin((x+1)*hangleStep)*bottomr,
                    std::cos((x+1)*hangleStep)*bottomr,
                    bottomz);
                scene->add(new Triangle(tleft,tright,bleft,texMapper,material));
                scene->add(new Triangle(bleft,bright,tright,texMapper,material));
            }
        }
    }


    void makeTesselatedSmoothSphere(Group*scene, const Point& center, float radius, int vtesselCount, int htesselCount, CoordMapper* texMapper, Material* material) {
        float vangleStep = pi / vtesselCount;
        float hangleStep = (2*pi) / htesselCount;

        //top and bottom cone
        {
            Point top = center + Vector(0,0,radius);
            Vector topN = Vector(0,0,1);
            Point bottom = center - Vector(0,0,radius);
            Vector bottomN = Vector(0,0,-1);

            float z = std::cos(vangleStep)*radius;
            float r = std::sin(vangleStep)*radius;
            for (int i=0; i<htesselCount; ++i) {
                Vector tleftN = Vector(std::sin(i*hangleStep)*r, std::cos(i*hangleStep)*r, z);
                Point tleft = center + tleftN;
                tleftN = tleftN.normalize();

                Vector trightN = Vector(std::sin((i+1)*hangleStep)*r, std::cos((i+1)*hangleStep)*r, z);
                Point tright = center + trightN;
                trightN = trightN.normalize();

                scene->add(new SmoothTriangle(top,tleft,tright,topN,tleftN,trightN,texMapper,material));
                Vector bleftN = Vector(std::sin(i*hangleStep)*r, std::cos(i*hangleStep)*r, -z);
                Point bleft = center + bleftN;
                bleftN = bleftN.normalize();

                Vector brightN = Vector(std::sin((i+1)*hangleStep)*r, std::cos((i+1)*hangleStep)*r, -z);
                Point bright = center + brightN;
                brightN = brightN.normalize();
                scene->add(new SmoothTriangle(bottom,bleft,bright,bottomN,bleftN,brightN,texMapper,material));
            }
        }

        //between top and bottom cones
        for (int y=1; y<vtesselCount-1; ++y) {
            float topz = std::cos(vangleStep*y)*radius;
            float bottomz = std::cos(vangleStep*(y+1))*radius;
            float topr = std::sin(vangleStep*y)*radius;
            float bottomr = std::sin(vangleStep*(y+1))*radius;
            for (int x=0; x<htesselCount; ++x) {
                Vector tleftN = Vector(std::sin(x*hangleStep)*topr, std::cos(x*hangleStep)*topr, topz);
                Point tleft = center + tleftN;
                tleftN = tleftN.normalize();

                Vector trightN = Vector(std::sin((x+1)*hangleStep)*topr, std::cos((x+1)*hangleStep)*topr, topz);
                Point tright = center + trightN;
                trightN = trightN.normalize();

                Vector bleftN = Vector(std::sin(x*hangleStep)*bottomr, std::cos(x*hangleStep)*bottomr, bottomz);
                Point bleft = center + bleftN;
                bleftN = bleftN.normalize();

                Vector brightN = Vector(std::sin((x+1)*hangleStep)*bottomr, std::cos((x+1)*hangleStep)*bottomr, bottomz);
                Point bright = center + brightN;
                brightN = brightN.normalize();
                scene->add(new SmoothTriangle(tleft,tright,bleft,tleftN,trightN,bleftN,texMapper,material));
                scene->add(new SmoothTriangle(bleft,bright,tright,bleftN,brightN,trightN,texMapper,material));
            }
        }
    }

}
