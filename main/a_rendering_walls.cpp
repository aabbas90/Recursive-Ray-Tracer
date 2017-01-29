
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
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/materials/combine.h>
#include <rt/materials/cookTorrance.h>

#include <rt/solids/quad.h>
#include <rt/solids/triangle.h>
#include <rt/solids/sphere.h>

#include <rt/coordmappers/plane.h>
#include <rt/coordmappers/cylindrical.h>
#include <rt/coordmappers/spherical.h>
#include <rt/coordmappers/tmapper.h>

#include <rt/integrators/recraytrace.h>


using namespace rt;
void a_rendering_walls()
{
    Image img(800, 600);


    // float xRotation = -15; //2_scene
    // float yRotation = -40;
    // float zRotation = 0;
    // Point cameraPostion = Point(-500, 200, 400);
    // Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    // Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);




    float xRotation = -15; //2_scene zoom
    float yRotation = -40;
    float zRotation = 0;
    Point cameraPostion = Point(-130, 85, 100);
    Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);

	Matrix rotationMatrix = getRotationMatrix(xRotation, yRotation, zRotation);
    upVector = rotationMatrix * upVector;
    forwardVector = rotationMatrix * forwardVector;

    // Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    // Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    // Texture* goldtex = new ConstantTexture(RGBColor(0.9f,0.9f,0.0f));
    // Texture* whitetex = new ConstantTexture(RGBColor(1.0f,1.0f,1.0f));
    // Texture* blacktex = new ConstantTexture(RGBColor(0.0f,0.0f,0.0f));

	// // Material* lamp_mat = new PhongMaterial(greentex, 20.0f);
	// Material* lamp_mat = new LambertianMaterial(bluetex, bluetex);
    // // Material* lamp_mat = new GlassMaterial(2.0f);
    // Material* other_mat = new LambertianMaterial(greentex, bluetex);
    // Material* wall_mat = new LambertianMaterial(bluetex, bluetex);
    // Material* gold_mat = new LambertianMaterial(goldtex, goldtex);
    // Material* white_mat = new LambertianMaterial(whitetex, whitetex);
    // Material* black_mat = new LambertianMaterial(blacktex, blacktex);
    // ImageTexture* woodtex = new ImageTexture("models/wood1.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    // FlatMaterial* woodtex_mat = new FlatMaterial(woodtex);



    // Material* mat_stones = new MirrorMaterial(0.0f, 0.0f);

    // MatLib* matlib = new MatLib;
    // matlib->insert(std::pair<std::string, Material*>("stage_floor_mat1", woodtex_mat)); 
    // matlib->insert(std::pair<std::string, Material*>("stage_floor_mat2", woodtex_mat)); 


    // matlib->insert(std::pair<std::string, Material*>("initialShadingGroup", other_mat)); 
    // matlib->insert(std::pair<std::string, Material*>("hemisphere_mat", lamp_mat)); 
    // matlib->insert(std::pair<std::string, Material*>("Piano1:Wood", woodtex_mat)); 
    // matlib->insert(std::pair<std::string, Material*>("Piano1:Gold", gold_mat)); 
    // matlib->insert(std::pair<std::string, Material*>("Piano1:Material_002", white_mat));
    // matlib->insert(std::pair<std::string, Material*>("Piano1:Material_004", black_mat));
    // matlib->insert(std::pair<std::string, Material*>("Piano1:Black", black_mat));

    // matlib->insert(std::pair<std::string, Material*>("wall_mat", wall_mat)); 
    // matlib->insert(std::pair<std::string, Material*>("celing_wall_mat", wall_mat)); 
    // matlib->insert(std::pair<std::string, Material*>("ground_mat", wall_mat)); 

    BVH* scene = new BVH(false);
    // loadOBJ(scene, "models/", "1_sph.obj", matlib);
    // loadOBJ(scene, "models/", "4_scene.obj", matlib);


    // BVH* stageTopLight = new BVH(false);
    // loadOBJ(stageTopLight, "models/", "1_light.obj");
    // stageTopLight->translate(Vector(85.0f,0.0f,-27));
    // scene->add(stageTopLight);




    Point b1(120, 145, -180);
    Point b2(120, 145, 180);
    Point b3(120, 0, -180);
    Point b4(120, 0, 180);

    Point f1(-360, 145, -180);
    Point f2(-360, 145, 180);
    Point f3(-360, 0, -180);
    Point f4(-360, 0, 180);

    ImageTexture* whitetex = new ImageTexture("models/stones_diffuse.png");
    ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    LambertianMaterial white(blacktex, whitetex);

    TriangleMapper* bottomleft = new TriangleMapper(Point(0,0,0), Point(3,0,0), Point(0,3,0));
    TriangleMapper* topright = new TriangleMapper(Point(3,3,0), Point(3,0,0), Point(0,3,0));
    
    //ceiling
    scene->add(new Triangle(b1, b2, f1), bottomleft, &white)); 
    scene->add(new Triangle(f2, b2, f1), topright, &white)); 

    //right wall
    scene->add(new Triangle(b4, f4, b2), bottomleft, &white)); 
    scene->add(new Triangle(f2, f4, b2), topright, &white)); 

    //left wall
    scene->add(new Triangle(f3, b3, f1), bottomleft, &white)); 
    scene->add(new Triangle(b1, b3, f1), topright, &white)); 

    //ground
    scene->add(new Triangle(f3, f4, b3, bottomleft, &white)); 
    scene->add(new Triangle(b4, f4, b3, topright, &white)); 

    //back wall
    scene->add(new Triangle(b3, b4, b1, bottomleft, &white)); 
    scene->add(new Triangle(b2, b4, b1, topright, &white)); 

    scene->rebuildIndex();
    World world;
	world.scene = scene;

    //directional light
    DirectionalLight dirl(Vector(0.2f,-0.5f,0.5f).normalize(), RGBColor(0.25f,0.25f,0.5f));
    world.light.push_back(&dirl);
    world.light.push_back(new SpotLight(Point(0.0f, 100.f, 0.f), Vector(0.2f, -1.0f, 0.0f).normalize(),  pi/4, 8.0f, RGBColor(0.0f,0.0f,1.0f)));

	// PerspectiveCamera cam1(Point(0.0f, 5.0f, 30.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f), pi / 4, pi / 3);
    // PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);
    PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);

    // RayCastingIntegrator integrator(&world);
    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
	engine1.setSamples(20);
    engine1.render(img);
    img.writePNG("1_walls.png");
}