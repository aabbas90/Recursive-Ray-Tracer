
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
#include <rt/lights/directional.h>
#include <rt/primmod/instance.h>
#include <core/matrix.h>

using namespace rt;
void a_rendering()
{
    Image img(80, 60);
	float xRotation = -110;
    float yRotation = 290;
    float zRotation = 0;
    Point cameraPostion = Point(-460, 95, 150);
    Vector upVector = Vector(1.0f, 0.0f, 0.0f);
    Vector forwardVector = Vector(1.0f, 0.0f, 0.0f);

    // float xRotation = 10;
    // float yRotation = 30;
    // float zRotation = 40;
    // Point cameraPostion = Point(35, 10, 55);
    // Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    // Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);

	Matrix rotationMatrix = getRotationMatrix(xRotation, yRotation, zRotation);
    upVector = rotationMatrix * upVector;
    forwardVector = rotationMatrix * forwardVector;


    BVH* scene = new BVH(false);
    loadOBJ(scene, "models/", "scene1.obj");
    scene->rebuildIndex();
    World world;
	world.scene = scene;

    //directional light
    DirectionalLight dirl(Vector(0.2f,-0.5f,0.5f).normalize(), RGBColor(0.25f,0.25f,0.5f));
    world.light.push_back(&dirl);

	// PerspectiveCamera cam1(Point(0.0f, 5.0f, 30.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f), pi / 4, pi / 3);
    PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);

    RayCastingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("scene1.png");
}