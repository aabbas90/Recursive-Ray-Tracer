
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
#include <rt/primmod/bmap.h>
#include <core/matrix.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/materials/combine.h>
#include <rt/materials/cookTorrance.h>
#include <rt/materials/cameraLCDMaterial.h>
#include <rt/materials/mirror.h>

#include <rt/solids/quad.h>
#include <rt/solids/triangle.h>
#include <rt/solids/sphere.h>

#include <rt/coordmappers/plane.h>
#include <rt/coordmappers/cylindrical.h>
#include <rt/coordmappers/spherical.h>
#include <rt/coordmappers/tmapper.h>

#include <rt/integrators/recraytrace.h>
#include <rt/lights/arealight.h>
#include <rt/lights/areaspotlight.h>
#include <core/random.h>
#include <rt/solids/disc.h>

using namespace rt;
void a_rendering_walls()
{
    Image img(800, 600);

	// Texture* greentex = new ConstantTexture(RGBColor(0.f, .7f, 0.f));
	// Texture* bluetex = new ConstantTexture(RGBColor(0.f, 0.f, 0.7f));
	// Texture* goldtex = new ConstantTexture(RGBColor(0.9f, 0.9f, 0.0f));
	// Texture* whitetex = new ConstantTexture(RGBColor(1.0f, 1.0f, 1.0f));

    // float xRotation = -15; //2_scene
    // float yRotation = -40;
    // float zRotation = 0;
    // Point cameraPostion = Point(-500, 200, 400);
    // Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    // Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);




	float xRotation = 0; // -15; //2_scene zoom //front view
	float yRotation = -451; // -40;
    float zRotation = 0;
    // Point cameraPostion = Point(-130, 85, 100);
	Point cameraPostion = Point(-350, 80, 0);
    Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);



	// float xRotation = 0;  //opposite view
	// float yRotation = -270; // -40;
    // float zRotation = 0;
    
	// Point cameraPostion = Point(0, 110, 0);
    // Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    // Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);


	Matrix rotationMatrix = getRotationMatrix(xRotation, yRotation, zRotation);
    upVector = rotationMatrix * upVector;
    forwardVector = rotationMatrix * forwardVector;

    Texture* greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    Texture* goldtex = new ConstantTexture(RGBColor(0.9f,0.9f,0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor(1.0f,1.0f,1.0f));
    Texture* blacktex1 = new ConstantTexture(RGBColor(0.0f,0.0f,0.0f));
	Texture* graytex1 = new ConstantTexture(RGBColor(0.1f, 0.1f, 0.1f));

	// Material* lamp_mat = new PhongMaterial(greentex, 20.0f);
	Material* lamp_mat = new LambertianMaterial(bluetex, bluetex);
    // Material* lamp_mat = new GlassMaterial(2.0f);
    Material* other_mat = new LambertianMaterial(greentex, bluetex);
    Material* wall_mat = new LambertianMaterial(bluetex, bluetex);
    Material* gold_mat = new LambertianMaterial(goldtex, goldtex);
    Material* white_mat = new LambertianMaterial(whitetex, whitetex);
    Material* black_mat = new LambertianMaterial(blacktex1, blacktex1);
	Material* gray_mat = new LambertianMaterial(graytex1, graytex1);
	ImageTexture* woodtex = new ImageTexture("models/wood1.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    FlatMaterial* woodtex_mat = new FlatMaterial(woodtex);

	Point pianoCentre = Point(-15, 0, -70);
    CombineMaterial* curtainMixedMat = new CombineMaterial();
	ImageTexture* curtaintex = new ImageTexture("models/curtain_tex.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    FlatMaterial* curtaintex_mat = new FlatMaterial(curtaintex);
    curtainMixedMat->add(new FlatMaterial(curtaintex), .05);
    curtainMixedMat->add(lamp_mat, .95);

	float f = 1;
	float cameraSizeX = 12;
	float cameraSizeY = 8;

	Point sceneCameraCentre = cameraPostion + forwardVector * 100 + cross(forwardVector, upVector).normalize() * 40 - upVector.normalize() * 20;
	
	Vector sceneCameraForwardVector = (pianoCentre - sceneCameraCentre).normalize();
	Vector sceneCameraRightVector = cross(sceneCameraForwardVector, upVector).normalize() * cameraSizeX;
	Vector sceneCameraUpVector = cross(sceneCameraRightVector, sceneCameraForwardVector).normalize() * cameraSizeY;

	Point sceneCameraLeftCorner = sceneCameraCentre - sceneCameraUpVector * 0.5 - sceneCameraRightVector.normalize() * 0.5;

	Material* camera_mat = new CameraLCDmaterial(sceneCameraCentre, sceneCameraLeftCorner, sceneCameraForwardVector, sceneCameraUpVector.normalize(), pi / 4, pi / 3, cameraSizeX, cameraSizeY, f);
	Quad* cameraQuad = new Quad(sceneCameraLeftCorner, sceneCameraUpVector, sceneCameraRightVector, nullptr, camera_mat);

    // Material* mat_stones = new MirrorMaterial(0.0f, 0.0f);

    MatLib* matlib = new MatLib;
    matlib->insert(std::pair<std::string, Material*>("stage_floor_mat1", woodtex_mat)); 
    matlib->insert(std::pair<std::string, Material*>("stage_floor_mat2", woodtex_mat)); 


	CombineMaterial* pianoBlackMat = new CombineMaterial();
	pianoBlackMat->add(new LambertianMaterial(blacktex1, blacktex1), 0.5);
	pianoBlackMat->add(new PhongMaterial(blacktex1, 30), 0.4);
	pianoBlackMat->add(new FuzzyMirrorMaterial(12.485f, 0.433f, 0.01f), 0.1);

	CombineMaterial* pianoWhiteMat = new CombineMaterial();
	pianoBlackMat->add(new LambertianMaterial(whitetex, whitetex), 0.1);
	pianoWhiteMat->add(new FuzzyMirrorMaterial(12.485f, 0.433f, 0.05f), 0.9);

	CombineMaterial* pianoGoldMat = new CombineMaterial();
	pianoGoldMat->add(new LambertianMaterial(blacktex1, goldtex), 0.5);
	pianoGoldMat->add(new PhongMaterial(goldtex, 10), 0.5);

    MirrorMaterial specsMirror(0.0f, 0.0f);

    matlib->insert(std::pair<std::string, Material*>("initialShadingGroup", other_mat)); 
    matlib->insert(std::pair<std::string, Material*>("hemisphere_mat", lamp_mat)); 
    matlib->insert(std::pair<std::string, Material*>("Piano1:Wood", pianoBlackMat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Gold", pianoBlackMat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Material_002", white_mat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Material_004", pianoBlackMat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Black", pianoBlackMat));

    matlib->insert(std::pair<std::string, Material*>("wall_mat", wall_mat)); 
    matlib->insert(std::pair<std::string, Material*>("celing_wall_mat", wall_mat)); 
    matlib->insert(std::pair<std::string, Material*>("ground_mat", wall_mat)); 
	matlib->insert(std::pair<std::string, Material*>("light_mat", gray_mat));
    matlib->insert(std::pair<std::string, Material*>("specs_mat", &specsMirror));
    matlib->insert(std::pair<std::string, Material*>("curtain_mat", curtainMixedMat));

    BVH* scene = new BVH(false);
    BVH* lightObj = new BVH(false);
    BVH* specs = new BVH(false);
    
    loadOBJ(scene, "models/", "1_piano.obj", matlib);
    //loadOBJ(scene, "models/", "1_piano_curtain.obj", matlib);
    loadOBJ(lightObj, "models/", "1_light_object.obj", matlib);
    loadOBJ(specs, "models/", "1_specs_mirror.obj", matlib);
	lightObj->rebuildIndex();

	scene->add(cameraQuad);
    specs->rebuildIndex();
    // scene->add(specs); //uncomment for specs
    // make instance etc

    // scene->add(lightObj);

  

    ImageTexture* woodTex = new ImageTexture("models/wood1.png");
    ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    LambertianMaterial woodMaterial(blacktex, woodTex);

    ImageTexture* stoneTex = new ImageTexture("models/stones_diffuse.png");
    LambertianMaterial stoneMaterial(blacktex, stoneTex);

    ImageTexture* claddingTex = new ImageTexture("models/a_cladding_tex.png");
    ImageTexture* claddingTexBump = new ImageTexture("models/a_cladding_tex_gray.png");
    LambertianMaterial claddingMat(blacktex, claddingTex);
 
	CombineMaterial* black_mat2 = new CombineMaterial();
	black_mat2->add(new PhongMaterial(whitetex, 1), 0.5);
	black_mat2->add(new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f), 0.25);
	black_mat2->add(new LambertianMaterial(blacktex, greentex), 0.25);

    CombineMaterial* specs_mat = new CombineMaterial();
	specs_mat->add(new PhongMaterial(whitetex, 10), 0.2);
	specs_mat->add(new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f), 0.8);

    Point lowerLeft(0,0,0);
    Point lowerRight(1,0,0);
    Point upperLeft(0,1,0);
    Point upperRight(1,1,0);
    TriangleMapper* bottomleft = new TriangleMapper(lowerLeft, lowerRight, upperLeft);
    TriangleMapper* topright = new TriangleMapper(upperRight, lowerRight, upperLeft);

    //stage cube
    Point bs1(32, 7, -80);
    Point bs2(32, 7, 80);
    Point bs3(32, 0, -80);
    Point bs4(32, 0, 80);

    Point fs1(-60, 7, -80);
    Point fs2(-60, 7, 80);
    Point fs3(-60, 0, -80);
    Point fs4(-60, 0, 80);

    //back stage wall
    Point w1(32, 113, -80);
    Point w2(32, 113, 80);

    //back stage wall TODO uncomment this later
    // scene->add(new Triangle(bs1, bs2, w1, bottomleft, &woodMaterial));
    // scene->add(new Triangle(w2, bs2, w1, topright, &woodMaterial));

    //stage front 
    scene->add(new Triangle(fs3, fs4, fs1, bottomleft, &woodMaterial));
    scene->add(new Triangle(fs2, fs4, fs1, topright, &woodMaterial));

    //stage ground 
    scene->add(new Triangle(fs1, fs2, bs1, bottomleft, &woodMaterial));
    scene->add(new Triangle(bs2, fs2, bs1, topright, &woodMaterial));

    //stage left 
    scene->add(new Triangle(bs3, fs3, bs1, bottomleft, &woodMaterial));
    scene->add(new Triangle(fs1, fs3, bs1, topright, &woodMaterial));

    //stage right 
    scene->add(new Triangle(fs4, bs4, fs2, bottomleft, &woodMaterial));
    scene->add(new Triangle(bs2, bs4, fs2, topright, &woodMaterial));

      //room cube
    Point b1(120, 145, -180);
    Point b2(120, 145, 180);
    Point b3(120, 0, -180);
    Point b4(120, 0, 180);

    Point f1(-360, 145, -180);
    Point f2(-360, 145, 180);
    Point f3(-360, 0, -180);
    Point f4(-360, 0, 180);

    float bumbscale = 0.9f;
    //back wall

    // scene->add(new Triangle(b3, b4, b1, bottomleft, &claddingMat));
    // scene->add(new Triangle(b2, b4, b1, topright, &claddingMat));

    scene->add(new BumpMapper(
            new Triangle(b3, b4, b1, bottomleft, &claddingMat), 
    claddingTexBump, lowerLeft, upperLeft, lowerRight, bumbscale));
    scene->add(
        new BumpMapper(
            new Triangle(b2, b4, b1, topright, &claddingMat),
    claddingTexBump, upperRight, lowerRight, upperLeft, bumbscale));


    // MirrorMaterial mirror(0.0f, 0.0f);
    // //front wall
    // scene->add(new Triangle(f3, f4, f1, bottomleft, &mirror));
    // scene->add(new Triangle(f2, f4, f1, topright, &mirror));

    //ceiling
    scene->add(new Triangle(b1, b2, f1, bottomleft, &woodMaterial)); 
    scene->add(new Triangle(f2, b2, f1, topright, &woodMaterial)); 

    //right wall
    scene->add(new Triangle(b4, f4, b2, bottomleft, &woodMaterial)); 
    scene->add(new Triangle(f2, f4, b2, topright, &woodMaterial)); 

    //left wall
    scene->add(new Triangle(f3, b3, f1, bottomleft, &woodMaterial)); 
    scene->add(new Triangle(b1, b3, f1, topright, &woodMaterial)); 

    //ground
    scene->add(new Triangle(f3, f4, b3, bottomleft, &woodMaterial)); 
    scene->add(new Triangle(b4, f4, b3, topright, &woodMaterial)); 

	ConstantTexture* lightsrctex = new ConstantTexture(RGBColor(10, 10, 10));
	Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);

	Vector rightQuadVector = cross(forwardVector, upVector) * 50;
	Vector forwardQuadVector = forwardVector * 50;
	Quad* areaLight1 = new Quad((b1 + b2 + f1 + f2) * 0.25 - rightQuadVector / 2 - forwardQuadVector / 2, rightQuadVector, forwardQuadVector, nullptr, lightsource);
	AreaLight als1(areaLight1);
	scene->add(areaLight1);


	rightQuadVector = cross(forwardVector, upVector) * 10;
	Vector upQuadVector = upVector * 10;
	Quad* areaLight2 = new Quad(cameraPostion - forwardVector * 10, rightQuadVector, upQuadVector, nullptr, lightsource);
	AreaLight als2(areaLight2);
	scene->add(areaLight2);

    World world;
	world.light.push_back(&als1);
	world.light.push_back(&als2);

    //directional light
    // DirectionalLight dirl(Vector(0.2f,-0.5f,0.5f).normalize(), RGBColor(RGBColor::rep(100)));
    // DirectionalLight dirl(forwardVector.normalize(), RGBColor(RGBColor::rep(100)));

    // world.light.push_back(&dirl);
    world.light.push_back(new SpotLight(Point(-70, 70, 5), forwardVector.normalize(),  pi, 10.0f, RGBColor(RGBColor::rep(100000))));

	int channel = 0;
	int direction = 0;
	Point originalSpotLightPoint = Point(23, 100, -70 + 16);
	for (int i = 0; i < 7; i++)
	{
		RGBColor color = RGBColor(0, 0, 0);

		if (i % 3 == 0)
			color = RGBColor(0, 0, 1);
		else if (i % 3 == 1)
			color = RGBColor(0, 1, 0);
		else
			color = RGBColor(1, 0, 0);

		Point currentSpotLightPoint = Point(23, 100, -70 + 16 * i);
		Point currentPianoPoint = pianoCentre + Vector(0, 0, 16 * i);
		Vector currentLightDirection = (currentPianoPoint - currentSpotLightPoint).normalize();

		Instance* currentLightObj = new Instance(lightObj);
		currentLightObj->translate(-1.0f * (originalSpotLightPoint - Point(0, 0, 0)));
		currentLightObj->rotate(Vector(0, 0, 1), atan(currentLightDirection.x / currentLightDirection.y));
		currentLightObj->translate(1.0f * (originalSpotLightPoint - Point(0, 0, 0)));
		currentLightObj->translate(Vector(0, 0, 16 * i));

		ConstantTexture* currentLightTex = new ConstantTexture(color * 10000);
		Material* currentSource = new LambertianMaterial(currentLightTex, goldtex);
		Point discCentre = Point(-22.782f, 113.576, -43.059) + currentLightDirection * 0.5 + Vector(0, 0, 16 * i);
		Disc* currentDisc = new Disc(discCentre, currentLightDirection, 3, nullptr, currentSource);
		
		AreaSpotLight* als1 = new AreaSpotLight(currentDisc, cross(forwardQuadVector, rightQuadVector).normalize(), pi / 4, 30, color * 100);
		world.light.push_back(new SpotLight(discCentre, currentLightDirection, pi / 6, 100.0f, 1000000 * color));
		// world.light.push_back(als1);
		scene->add(currentDisc);
		scene->add(currentLightObj);
	}

	scene->rebuildIndex();
	world.scene = scene;

	// PerspectiveCamera cam1(Point(0.0f, 5.0f, 30.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f), pi / 4, pi / 3);
    // PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);
    PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);

    // RayCastingIntegrator integrator(&world);
    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
	engine1.setSamples(10);
    engine1.render(img);
    img.writePNG("1_walls.png");
}