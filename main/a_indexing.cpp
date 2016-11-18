#include <rt/solids/triangle.h>
#include <rt/solids/aabox.h>
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/kdtree.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/groups/simplegroup.h>


using namespace rt;

void a_indexing() {
	Image img(800, 600);
	
	BVH* scene = new BVH();
	// scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
	// scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
	// scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));

	//loadOBJ(scene, "models/", "cow.obj");
  
	// Uncomment after BVH:
	// scene->rebuildIndex();
	// World world;
	// world.scene = scene;

	// PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f,1.0f,-0.6f), Vector(0, 0, 1), pi/8, pi/6);
	// PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);
	// RayCastingIntegrator integrator(&world);

	// Renderer engine1(&cam1, &integrator);
	// engine1.render(img);
	// img.writePNG("a3-1.png");

	// Renderer engine2(&cam2, &integrator);
	// engine2.render(img);
	// img.writePNG("a3-2.png");


	loadOBJ(scene, "models/", "cow.obj");
	// scene->add(new Sphere(Point(-2.2f, 1.7f, 0), 2, nullptr, nullptr));
	// scene->add(new Sphere(Point(1, -1, 1), 2.2f, nullptr, nullptr));
	// scene->add(new Sphere(Point(3.f, 0.8f, -2), 2, nullptr, nullptr));

	// scene->add(new Triangle(Point(-2.01, 3.7f, 0), Point(1, 2, 1), Point(3, 2.8f, -2), nullptr, nullptr));
	// scene->add(new Triangle(Point(3, 2, 3), Point(3, 2, -3), Point(-3, 2, -3), nullptr, nullptr));

	// scene->add(new AABox(Point(2.01, 1.5f, -0.5f), Point(3, 2.5f, 2.5f), nullptr, nullptr));
	scene->rebuildIndex();
	

	World world;
	world.scene = scene;

	PerspectiveCamera cam(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi / 4, pi / 3);
	RayCastingIntegrator integrator(&world);
	Renderer engine(&cam, &integrator);
	engine.render(img);
	img.writePNG("a3-1.png");
}
