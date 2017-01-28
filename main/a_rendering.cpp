
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

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/materials/combine.h>
#include <rt/materials/cookTorrance.h>

#include <rt/integrators/recraytrace.h>


using namespace rt;
void a_rendering()
{
    Image img(800, 600);
	// float xRotation = -6;
    // float yRotation = -70;
    // float zRotation = 0;
    // Point cameraPostion = Point(-400, 90, 100);
    // Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    // Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);


    float xRotation = 0;
    float yRotation = 0;
    float zRotation = 0;
    Point cameraPostion = Point(0, 0, 12);
    Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);

    // float xRotation = 10;
    // float yRotation = 30;
    // float zRotation = 40;
    // Point cameraPostion = Point(35, 10, 55);
    // Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    // Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);

	Matrix rotationMatrix = getRotationMatrix(xRotation, yRotation, zRotation);
    upVector = rotationMatrix * upVector;
    forwardVector = rotationMatrix * forwardVector;

    Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));

	Material* mat_stones = new PhongMaterial(greentex, 20.0f);
    // Material* mat_stones = new LambertianMaterial(greentex, bluetex);
    // Material* mat_stones = new MirrorMaterial(0.0f, 0.0f);

    MatLib* matlib = new MatLib;
    matlib->insert(std::pair<std::string, Material*>("sph_mat", mat_stones)); 
    // matlib->insert(std::pair<std::string, Material*>("blinn1SG", mat_stones)); 


    BVH* scene = new BVH(false);
    loadOBJ(scene, "models/", "1_sph.obj", matlib);


    // BVH* stageTopLight = new BVH(false);
    // loadOBJ(stageTopLight, "models/", "1_light.obj");
    // stageTopLight->translate(Vector(85.0f,0.0f,-27));
    // scene->add(stageTopLight);

    scene->rebuildIndex();
    World world;
	world.scene = scene;

    //directional light
    DirectionalLight dirl(Vector(0.2f,-0.5f,0.5f).normalize(), RGBColor(0.25f,0.25f,0.5f));
    world.light.push_back(&dirl);

	// PerspectiveCamera cam1(Point(0.0f, 5.0f, 30.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f), pi / 4, pi / 3);
    // PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);
    PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);

    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("1_sph.png");
}