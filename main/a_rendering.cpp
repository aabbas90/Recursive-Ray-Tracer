
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
#include <rt/cameras/dofperspective.h>
#include <rt/integrators/casting.h>
#include <rt/lights/directional.h>
#include <rt/lights/spotlight.h>
#include <rt/primmod/instance.h>
#include <core/matrix.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials//fuzzymirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/materials/combine.h>
#include <rt/materials/cookTorrance.h>

#include <rt/integrators/recraytrace.h>
#include <rt/solids/disc.h>
#include <rt/world.h>
#include <rt/lights/arealight.h>

using namespace rt;
void a_rendering()
{
    Image img(400, 300);

    float xRotation = -15; //2_scene zoom
    float yRotation = -40;
    float zRotation = 0;
    Point cameraPostion = Point(-130, 85, 100);

    Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);

	Matrix rotationMatrix = getRotationMatrix(xRotation, yRotation, zRotation);
    upVector = rotationMatrix * upVector;
    forwardVector = rotationMatrix * forwardVector;

    Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    Texture* goldtex = new ConstantTexture(RGBColor(0.9f,0.9f,0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor(1.0f,1.0f,1.0f));
    Texture* blacktex = new ConstantTexture(RGBColor(0,0,0));

	// Material* lamp_mat = new PhongMaterial(greentex, 20.0f);
	CombineMaterial* lamp_mat = new CombineMaterial();
	lamp_mat->add(new PhongMaterial(whitetex, 10), 0.5);
	lamp_mat->add(new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f), 0.5);

    // Material* lamp_mat = new GlassMaterial(2.0f);
    Material* other_mat = new LambertianMaterial(greentex, bluetex);
    Material* wall_mat = new LambertianMaterial(bluetex, bluetex);
    Material* gold_mat = new LambertianMaterial(goldtex, goldtex);
    Material* white_mat = new LambertianMaterial(whitetex, whitetex);
	CombineMaterial* black_mat = new CombineMaterial();
	black_mat->add(new PhongMaterial(whitetex, 10), 0.5);
	black_mat->add(new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f), 0.5);

    ImageTexture* woodtex = new ImageTexture("models/wood1.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    FlatMaterial* woodtex_mat = new FlatMaterial(woodtex);

    MatLib* matlib = new MatLib;
    matlib->insert(std::pair<std::string, Material*>("stage_floor_mat1", woodtex_mat)); 
    matlib->insert(std::pair<std::string, Material*>("stage_floor_mat2", woodtex_mat)); 


    matlib->insert(std::pair<std::string, Material*>("initialShadingGroup", other_mat)); 
    matlib->insert(std::pair<std::string, Material*>("hemisphere_mat", lamp_mat)); 
    matlib->insert(std::pair<std::string, Material*>("Piano1:Wood", woodtex_mat)); 
    matlib->insert(std::pair<std::string, Material*>("Piano1:Gold", gold_mat)); 
    matlib->insert(std::pair<std::string, Material*>("Piano1:Material_002", white_mat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Material_004", black_mat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Black", black_mat));

    matlib->insert(std::pair<std::string, Material*>("wall_mat", wall_mat)); 
    matlib->insert(std::pair<std::string, Material*>("celing_wall_mat", wall_mat)); 
    matlib->insert(std::pair<std::string, Material*>("ground_mat", wall_mat)); 

    BVH* scene = new BVH(false);
    // loadOBJ(scene, "models/", "1_sph.obj", matlib);
    loadOBJ(scene, "models/", "4_scene.obj", matlib);


    // BVH* stageTopLight = new BVH(false);
    // loadOBJ(stageTopLight, "models/", "1_light.obj");
    // stageTopLight->translate(Vector(85.0f,0.0f,-27));
    // scene->add(stageTopLight);

	ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(25.0f));
	Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);

	// AreaLight als(light);
	// scene->add(light);


    World world;

	world.scene = scene;
	// world.light.push_back(&als);

    //directional light
	world.light.push_back(new SpotLight(Point(0, 60, 0), Vector(0, -1.0f, 0), pi / 8, 8.0f, RGBColor(1000, 1000, 1000)));
    DirectionalLight dirl(Vector(0.2f,-0.5f,0.5f).normalize(), RGBColor(0.25f,0.25f,0.5f));
    world.light.push_back(&dirl);
//    world.light.push_back(new SpotLight(Point(0.0f, 100.f, 0.f), Vector(0.2f, -1.0f, 0.0f).normalize(),  pi/4, 8.0f, RGBColor(0.0f,0.0f,1.0f)));

	// PerspectiveCamera cam1(Point(0.0f, 5.0f, 30.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f), pi / 4, pi / 3);
    // PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);
    PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);
	// DOFPerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3, 10, 0.025);
	scene->rebuildIndex();

    // RayCastingIntegrator integrator(&world);
    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
	engine1.setSamples(1);
    engine1.render(img);
    img.writePNG("3_scene.png");
}