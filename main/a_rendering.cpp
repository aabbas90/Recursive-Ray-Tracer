
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/kdtree.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>

using namespace rt;
void a_rendering()
{
    Image img(800, 600);
    
    BVH* scene = new BVH(false);
    loadOBJ(scene, "models/", "stage1.obj");
    scene->rebuildIndex();
    World world;
	world.scene = scene;


	PerspectiveCamera cam1(Point(0.0f, 2.0f, 20.0f), Vector(0.0f, 0.0f, 1.0f), Vector(0.0f, 1.0f, 0.0f), pi / 4, pi / 3);

    RayCastingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("1_stage1.png");
}