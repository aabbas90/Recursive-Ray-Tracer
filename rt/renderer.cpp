#include "renderer.h"
#include "ray.h"
#include "cameras\orthographic.h"

using namespace rt;

RGBColor a1computeColor(uint x, uint y, uint width, uint height);
RGBColor a2computeColor(const Ray& r);

Renderer::Renderer(Camera * cam, Integrator * integrator)
{
	this->cam = cam;
	this->integrator = integrator;
}

void Renderer::setSamples(uint samples)
{
	this->samples = samples;
}

void Renderer::render(Image & img)
{
}

void Renderer::test_render2(Image & img)
{
	for (uint i = 0; i < img.width(); ++i) 
	{
		float ii = 2.0 * i / img.width() - 1;
		for (uint j = 0; j < img.height(); ++j) 
		{
			float jj = 2.0 * j / img.height() - 1;
			Ray currentRay = cam->getPrimaryRay(ii, jj);
			img(i, j) = a2computeColor(currentRay);
		}
	}
}

void Renderer::test_render1(Image& img) {
	for (uint i = 0; i < img.width(); ++i) {
		for (uint j = 0; j < img.height(); ++j) {
			//TODO: Check if width and height passed are correct
			img(i, j) = a1computeColor(i, j, img.width(), img.height());
		}
	}
}

