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
#include <rt/lights/pointlight.h>
#include <core/random.h>
#include <rt/solids/disc.h>

using namespace rt;
void Render_Piano_Scene()
{
    Image img(1920, 1200);
	int numSamples = 10;

	// Changing direction:

	Point cameraPostion = Point(-220, 75, 62);

	float xRotation = -32; float yRotation = -67; float zRotation = -25;

    Vector upVector = Vector(0.0f, 1.0f, 0.0f);
    Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);

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
	Material* lamp_mat = new LambertianMaterial(blacktex1, bluetex);
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

	// Scene Camera:
	float f = 1;
	float cameraSizeX = 24;
	float cameraSizeY = 15;

	Point sceneCameraCentre = Point(-128, 35, -26); // cameraPostion + forwardVector * 100 + cross(forwardVector, upVector).normalize() * 40 - upVector.normalize() * 20;

	float camXRot = 0;
	float camYRot = 90;
	float camZRot = 0;

	Matrix camRotationMatrix = getRotationMatrix(camXRot, camYRot, camZRot);

	Vector sceneCameraUpVector = Vector(0, 1, 0.0f) * cameraSizeY; // (camRotationMatrix *  Vector(0.0f, 1.0f, 0.0f)).normalize() * cameraSizeY;
	Vector sceneCameraForwardVector = Vector(1, 0.0f, 0); // -(camRotationMatrix *  Vector(0.0f, 0.0f, -1.0f)).normalize();
	Vector sceneCameraRightVector = Vector(0, 0, 1) * cameraSizeX; // cross(sceneCameraForwardVector, upVector).normalize() * cameraSizeX;

	Point sceneCameraLeftCorner = sceneCameraCentre - sceneCameraUpVector * 0.5 - sceneCameraRightVector * 0.5;

	Material* camera_mat = new CameraLCDmaterial(sceneCameraCentre, sceneCameraLeftCorner, sceneCameraForwardVector, sceneCameraUpVector.normalize(), pi / 4, pi / 3, cameraSizeX, cameraSizeY, f);
	Quad* cameraQuad = new Quad(sceneCameraLeftCorner, sceneCameraUpVector, sceneCameraRightVector, nullptr, camera_mat);

    MatLib* matlib = new MatLib;
    matlib->insert(std::pair<std::string, Material*>("stage_floor_mat1", woodtex_mat)); 
    matlib->insert(std::pair<std::string, Material*>("stage_floor_mat2", woodtex_mat)); 

	Texture* impureBlacktex = new ConstantTexture(RGBColor(0.07f, 0.05f, 0.05f));
	// LambertianMaterial* pianoBlackMat = new LambertianMaterial(impureBlacktex, impureBlacktex);

	CombineMaterial* pianoBlackMat = new CombineMaterial();
	pianoBlackMat->add(new LambertianMaterial(impureBlacktex, impureBlacktex), 0.4f);
	pianoBlackMat->add(new PhongMaterial(impureBlacktex, 10), 0.1);
	pianoBlackMat->add(new FuzzyMirrorMaterial(2.485f, 3.433f, 0.01f), 0.5f);

	CombineMaterial* pianoWhiteMat = new CombineMaterial();
	pianoWhiteMat->add(new LambertianMaterial(whitetex, whitetex), 0.4f);
	pianoBlackMat->add(new PhongMaterial(impureBlacktex, 10), 0.1);
	pianoWhiteMat->add(new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f), 0.5f);

	CombineMaterial* pianoGoldMat = new CombineMaterial();
	pianoGoldMat->add(new LambertianMaterial(goldtex, goldtex), 0.5);
	pianoGoldMat->add(new FuzzyMirrorMaterial(1.5485f, 0.433f, 0.1f), 0.5);

    matlib->insert(std::pair<std::string, Material*>("initialShadingGroup", other_mat)); 
    matlib->insert(std::pair<std::string, Material*>("hemisphere_mat", lamp_mat)); 
    matlib->insert(std::pair<std::string, Material*>("Piano1:Wood", pianoBlackMat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Gold", pianoBlackMat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Material_002", pianoWhiteMat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Material_004", pianoBlackMat));
    matlib->insert(std::pair<std::string, Material*>("Piano1:Black", pianoBlackMat));

    matlib->insert(std::pair<std::string, Material*>("wall_mat", wall_mat)); 
    matlib->insert(std::pair<std::string, Material*>("celing_wall_mat", wall_mat)); 
    matlib->insert(std::pair<std::string, Material*>("ground_mat", wall_mat)); 
	matlib->insert(std::pair<std::string, Material*>("light_mat", gray_mat));
    matlib->insert(std::pair<std::string, Material*>("chair:Material_001", lamp_mat));

	Texture* cameraColor = new ConstantTexture(RGBColor::rep(0.2));
	CombineMaterial* cameraMaterial = new CombineMaterial();
	cameraMaterial->add(new LambertianMaterial(blacktex1, cameraColor), 0.75);
	cameraMaterial->add(new MirrorMaterial(2.485f, 3.433f), 0.25);

	matlib->insert(std::pair<std::string, Material*>("camera_view_mat", cameraMaterial));
	matlib->insert(std::pair<std::string, Material*>("tripod_mat", cameraMaterial));

    BVH* scene = new BVH(false);
    BVH* lightObj = new BVH(false);
    // BVH* specs = new BVH(false);
    BVH* chair = new BVH(false);
    
    loadOBJ(scene, "models/", "1_piano_rotated.obj", matlib);
	loadOBJ(scene, "models/", "1_camera.obj", matlib);
    loadOBJ(lightObj, "models/", "1_light_object.obj", matlib);
    loadOBJ(chair, "models/", "1_chair.obj", matlib);
	lightObj->rebuildIndex();
    chair->rebuildIndex();
	scene->add(cameraQuad);

    ImageTexture* woodTex = new ImageTexture("models/wood1.png");
    ConstantTexture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    LambertianMaterial woodMaterial(blacktex, woodTex);

    ImageTexture* stoneTex = new ImageTexture("models/stones_diffuse.png");
    LambertianMaterial stoneMaterial(blacktex, stoneTex);

    ImageTexture* claddingTex = new ImageTexture("models/a_cladding_tex2.png");
    ImageTexture* claddingTexBump = new ImageTexture("models/a_cladding_tex_gray.png");
    LambertianMaterial claddingMat(blacktex, claddingTex);
 
	CombineMaterial* black_mat2 = new CombineMaterial();
	black_mat2->add(new PhongMaterial(whitetex, 1), 0.5);
	black_mat2->add(new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f), 0.25);
	black_mat2->add(new LambertianMaterial(blacktex, greentex), 0.25);

    Point lowerLeft(0,0,0);
    Point lowerRight(1,0,0);
    Point upperLeft(0,1,0);
    Point upperRight(1,1,0);

    TriangleMapper* bottomleft = new TriangleMapper(lowerLeft, lowerRight, upperLeft);
    TriangleMapper* topright = new TriangleMapper(upperRight, lowerRight, upperLeft);

	float scale = 0.5f;
	TriangleMapper* bottomleft1 = new TriangleMapper(lowerLeft * scale, lowerRight * scale, upperLeft * scale);
	TriangleMapper* topright1 = new TriangleMapper(upperRight * scale, lowerRight * scale, upperLeft * scale);

    //stage cube
    Point bs1(42, 7, -80);
    Point bs2(42, 7, 80);
    Point bs3(42, 0, -80);
    Point bs4(42, 0, 80);

    Point fs1(-60, 7, -80);
    Point fs2(-60, 7, 80);
    Point fs3(-60, 0, -80);
    Point fs4(-60, 0, 80);

    //back stage wall
    Point w1(42, 113, -80);
    Point w2(42, 113, 80);

    //stage front 
    scene->add(new Triangle(fs3, fs4, fs1, bottomleft, &woodMaterial));
    scene->add(new Triangle(fs2, fs4, fs1, topright, &woodMaterial));

    //stage ground 
    scene->add(new Triangle(fs1, fs2, bs1, bottomleft, &woodMaterial));
    scene->add(new Triangle(bs2, fs2, bs1, topright, &woodMaterial));

	FuzzyMirrorMaterial *leftWallMirror = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.01f); // , 0.05f);

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


    float bumbscale = 1;

    scene->add(new BumpMapper(
            new Triangle(b3, b4, b1, bottomleft, &claddingMat), 
    claddingTex, lowerLeft, lowerRight, upperLeft, bumbscale));
    scene->add(
        new BumpMapper(
            new Triangle(b2, b4, b1, topright, &claddingMat),
    claddingTex, upperRight, lowerRight, upperLeft, bumbscale));

    //ceiling
    scene->add(new Triangle(b1, b2, f1, nullptr, leftWallMirror));
    scene->add(new Triangle(f2, b2, f1, nullptr, leftWallMirror));

    //right wall
    scene->add(new Triangle(b4, f4, b2, nullptr, &woodMaterial));
    scene->add(new Triangle(f2, f4, b2, nullptr, &woodMaterial));

    //left wall
    scene->add(new Triangle(f3, b3, f1, nullptr, leftWallMirror));
    scene->add(new Triangle(b1, b3, f1, nullptr, leftWallMirror));

	scene->add(new BumpMapper(
		new Triangle(f3, f4, b3, bottomleft, &woodMaterial),
		woodTex, lowerLeft, lowerRight, upperLeft, bumbscale));
	scene->add(
		new BumpMapper(
			new Triangle(b4, f4, b3, topright, &woodMaterial),
			woodTex, upperRight, lowerRight, upperLeft, bumbscale));

	ConstantTexture* lightsrctex = new ConstantTexture(RGBColor(10, 10, 10));
	ConstantTexture* arealightsrctex = new ConstantTexture(RGBColor::rep(50));
	Material* lightsource = new LambertianMaterial(arealightsrctex, blacktex);

	Vector rightQuadVector = cross(forwardVector, upVector) * 100;
	Vector forwardQuadVector = forwardVector * 20;
	Quad* areaLight1 = new Quad((b1 + b2 + f1 + f2) * 0.25 - rightQuadVector / 2 - forwardQuadVector / 2, rightQuadVector, forwardQuadVector, nullptr, lightsource);
	AreaLight als1(areaLight1);

    World world;

	Point p1 = f1 - (f1 - b4).normalize();
	Point p2 = f2 - (f2 - b3).normalize();
	Point p3 = f3 - (f3 - b2).normalize();
	Point p4 = f4 - (f4 - b1).normalize();

	float pointLightInt = 60000;

	world.light.push_back(new PointLight(f3 - (f3 - b2).normalize(), RGBColor::rep(pointLightInt)));
	world.light.push_back(new PointLight(f4 - (f4 - b1).normalize(), RGBColor::rep(pointLightInt)));

	world.light.push_back(new PointLight((p1 + p2) * 0.5f, RGBColor::rep(pointLightInt * 2)));

    // world.light.push_back(&dirl);
	Vector spotLightFV = (Point(-22.2028809, 23.1722298, -1.95628357) - sceneCameraCentre).normalize();// sceneCameraForwardVector.normalize() + sceneCameraRightVector.normalize() * 0.2 + sceneCameraUpVector.normalize() * 0.1;
    world.light.push_back(new SpotLight(sceneCameraCentre + sceneCameraForwardVector.normalize() * 0.2, spotLightFV,  pi / 3, 300.0f, RGBColor(RGBColor::rep(100))));

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

		Point currentSpotLightPoint = Point(23, 131, -70 + 16 * (i + 1)); // Point(50, 100, -70 + 16 * i);
		Point currentPianoPoint = pianoCentre + Vector(100, 0, 16 * (i + 1));
		Vector currentLightDirection = (currentPianoPoint - currentSpotLightPoint).normalize();

		Instance* currentLightObj = new Instance(lightObj);
		currentLightObj->translate(-1.0f * (originalSpotLightPoint - Point(0, 0, 0))); 
		currentLightObj->rotate(Vector(0, 0, 1), atan(currentLightDirection.x / currentLightDirection.y));
		currentLightObj->translate(1.0f * (originalSpotLightPoint - Point(0, 0, 0)));
		currentLightObj->translate(currentSpotLightPoint - originalSpotLightPoint);

		ConstantTexture* currentLightTex = new ConstantTexture(color * 10000);
		Material* currentSource = new LambertianMaterial(currentLightTex, blacktex);
		// Point discCentre = Point(35.73, 115.87, -43) + currentLightDirection * 0.5 + Vector(0, 0, 16 * i);
		Point discCentre = Point(-62.5809021, 96.7399216, -44.2987137) + currentLightDirection * 0.5 + Vector(0, 0, 16 * i);

		Disc* currentDisc = new Disc(discCentre, currentLightDirection, 3, nullptr, currentSource);

		AreaSpotLight* als1 = new AreaSpotLight(currentDisc, currentLightDirection, pi / 1.5, 50, color * 0.5f);
		world.light.push_back(als1);
		world.light.push_back(new SpotLight(discCentre, currentLightDirection, pi / 1.5, 50, 100000 * color));
		// scene->add(currentDisc);
		// scene->add(currentLightObj);
	}

	scene->rebuildIndex();
	world.scene = scene;

    PerspectiveCamera cam1(cameraPostion, forwardVector, upVector, pi / 4, pi / 3);

    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine1(&cam1, &integrator);
	engine1.setSamples(numSamples);
    engine1.render(img);
    img.writePNG("example Images/Piano_scene.png");
}