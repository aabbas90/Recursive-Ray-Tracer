#include "renderer.h"

using namespace rt;

RGBColor a1computeColor(uint x, uint y, uint width, uint height);

Renderer::Renderer(Camera * cam, Integrator * integrator)
{
}

void Renderer::setSamples(uint samples)
{
}

void Renderer::render(Image & img)
{
}

void Renderer::test_render2(Image & img)
{
}

void Renderer::test_render1(Image& img) {
	for (uint i = 0; i < img.width(); ++i) {
		for (uint j = 0; j < img.height(); ++j) {
			//TODO: Check if width and height passed are correct
			img(i, j) = a1computeColor(i, j, img.width(), img.height());
		}
	}
}

