#include <rt/renderer.h>
#include <rt/ray.h>
#include <rt/cameras/orthographic.h>
#include <rt/integrators/integrator.h>
#include <core/random.h>

using namespace rt;

RGBColor a1computeColor(uint x, uint y, uint width, uint height);
RGBColor a2computeColor(const Ray& r);

Renderer::Renderer(Camera * cam, Integrator * integrator)
{
	this->cam = cam;
	this->integrator = integrator;
	this->samples = 1;
}

void Renderer::setSamples(uint samples)
{
	this->samples = samples;
}

void Renderer::render(Image & img)
{
	if(samples > 1)
	{
		for (uint i = 0; i < img.width(); ++i)
		{
			
			for (uint j = 0; j < img.height(); ++j)
			{
				RGBColor color = RGBColor::black();
				if (i == 200 && j == 153)
				{
					i = i;
				}

				for(uint s = 0; s < samples; ++s)
				{

					float ii = 2.0 * (i + random()) / img.width() - 1;
					float jj = 2.0 * (j + random()) / img.height() - 1;
					Ray currentRay = cam->getPrimaryRay(ii, jj);
					color = color + integrator->getRadiance(currentRay);
				}
				//Regular super-sampling Averaging of N samples per pixel
				img(i, j) = color / samples;
			}
		}
	}
	else
	{
		for (uint i = 0; i < img.width(); ++i)
		{
			float ii = 2.0 * (i + 0.5) / img.width() - 1;
			for (uint j = 0; j < img.height(); ++j)
			{
				float jj = 2.0 * (j + 0.5) / img.height() - 1;
				Ray currentRay = cam->getPrimaryRay(ii, jj);

				img(i, j) = integrator->getRadiance(currentRay);
			}
		}
	}
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

			if (currentRay.d == Vector(0,0,0))
				img(i, j) = RGBColor(0,0,0);

			else
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

