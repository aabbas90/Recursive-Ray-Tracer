
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
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif
using namespace rt;
typedef long long int64; typedef unsigned long long uint64;

uint64 GetTimeMs64()
{
#ifdef _WIN32
	/* Windows */
	FILETIME ft;
	LARGE_INTEGER li;

	/* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
	* to a LARGE_INTEGER structure. */
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;

<<<<<<< HEAD
void a_indexing() {
	Image img(800, 600);

	//SimpleGroup* scene = new SimpleGroup();

	// Uncomment after BVH:
	BVH* scene = new BVH();
	scene->add(new Sphere(Point(2.5f, .5f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(2.5f, -1.f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(4.5f, .5f, -1), 0.5, nullptr, nullptr));

	loadOBJ(scene, "models/", "cow.obj");

	// Uncomment after BVH:
	scene->rebuildIndex();
=======
	uint64 ret = li.QuadPart;
	ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
	ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

	return ret;
#else
	/* Linux */
	struct timeval tv;

	gettimeofday(&tv, NULL);

	uint64 ret = tv.tv_usec;
	/* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
	ret /= 1000;

	/* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
	ret += (tv.tv_sec * 1000);

	return ret;
#endif
}

void a_indexing(bool doSAH) {
	Image img(800, 600);

	std::cout << "SAH Running ==" << doSAH << std::endl;
	BVH* scene = new BVH(doSAH);
	scene->add(new Sphere(Point(2.5f, .5f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(2.5f, -1.f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(4.5f, .5f, -1), 0.5, nullptr, nullptr));

	loadOBJ(scene, "models/", "cow.obj");

	auto startTime = GetTimeMs64();
	scene->rebuildIndex();
	auto endTime = GetTimeMs64();
	std::cout << "Tree building time(ms): " << endTime - startTime << std::endl;
>>>>>>> chitra
	World world;
	world.scene = scene;

	PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f, 1.0f, -0.6f), Vector(0, 0, 1), pi / 8, pi / 6);
	PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f) - Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi / 8, pi / 6);
<<<<<<< HEAD
	RayCastingIntegrator integrator(&world);

	Renderer engine1(&cam1, &integrator);
	engine1.render(img);
	img.writePNG("a3-1.png");

	Renderer engine2(&cam2, &integrator);
	engine2.render(img);
	img.writePNG("a3-2.png");
=======
	PerspectiveCamera cam3(Point(0, 4, -30), Vector(0, 0, 1), Vector(0, 1, 0), pi / 8, pi / 6);

	RayCastingIntegrator integrator(&world);

	Renderer engine1(&cam1, &integrator);
	startTime = GetTimeMs64();
	engine1.render(img);
	endTime = GetTimeMs64();
	std::cout << "Image 1 rendering time(ms): " << endTime - startTime << std::endl;
	if (!doSAH)
		img.writePNG("a3-1-WithoutSAH.png");
	else
		img.writePNG("a3-1-WithSAH.png");

	Renderer engine2(&cam2, &integrator);
	startTime = GetTimeMs64();
	engine2.render(img);
	endTime = GetTimeMs64();
	std::cout << "Image 2 rendering time(ms): " << endTime - startTime << std::endl << std::endl << std::endl << std::endl;
	if (!doSAH)
		img.writePNG("a3-2-WithoutSAH.png");
	else
		img.writePNG("a3-2-WithSAH.png");

	World world2;

	BVH* scene2 = new BVH(doSAH);
	world2.scene = scene2;
	RayCastingIntegrator integrator2(&world2);

	loadOBJ(scene2, "models/", "dragon.obj");
	
	 startTime = GetTimeMs64();
	scene2->rebuildIndex();
	 endTime = GetTimeMs64();
	std::cout << "Tree building time(ms): " << endTime - startTime << std::endl;

	Renderer engine3(&cam3, &integrator2);
	startTime = GetTimeMs64();
	engine3.render(img);
	endTime = GetTimeMs64();
	std::cout << "Image 3 (Dragon) rendering time(ms): " << endTime - startTime << std::endl << std::endl << std::endl << std::endl;
	if (!doSAH)
		img.writePNG("a3-3-WithoutSAH.png");
	else
		img.writePNG("a3-3-WithSAH.png");


>>>>>>> chitra
}
