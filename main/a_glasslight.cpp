
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
#include <rt/lights/spotlight.h>

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
void a_glasslight()
{
    Image img(800, 600);

    float xRotation = 0;
    float yRotation = 0;
    float zRotation = 0;
    Point cameraPostion = Point(0, 8, -6);
    Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);


	Matrix rotationMatrix = getRotationMatrix(xRotation, yRotation, zRotation);
    upVector = rotationMatrix * upVector;
    forwardVector = rotationMatrix * forwardVector;

    Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));

	Material* mat_stones = new PhongMaterial(greentex, 20.0f);
    // Material* mat_stones = new LambertianMaterial(greentex, bluetex);
    // Material* mat_stones = new MirrorMaterial(0.0f, 0.0f);

    MatLib* matlib = new MatLib;
    matlib->insert(std::pair<std::string, Material*>("hemisphere_mat", mat_stones)); 


    BVH* scene = new BVH(false);
    // loadOBJ(scene, "models/", "1_light_wall.obj", matlib);
    loadOBJ(scene, "models/", "2_light_wall.obj");

    scene->rebuildIndex();
    World world;
	world.scene = scene;

    //directional light
    DirectionalLight dirl(Vector(0.2f,-0.5f,0.5f).normalize(), RGBColor(0.25f,0.25f,0.5f));
    world.light.push_back(&dirl);

    // world.light.push_back(new SpotLight(Point(0.0f, 5.f, 3.f), Vector(0.0f, 0.0f, -1.0f),  pi/4, 8.0f, RGBColor(0.6f,0,0)));

    PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);

    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("1_light_wall.png");
}