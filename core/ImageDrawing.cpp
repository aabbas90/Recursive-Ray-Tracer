#include"ImageDrawing.h"

using namespace rt;

void DrawImage::displayImage(Image image)
{
	cimg_library::CImg<float> img(image.width(), image.height(), 1, 3, 0);
	for (uint i = 0; i < image.height(); i++)
	{
		for (uint j = 0; j < image.width(); j++)
		{
			RGBColor value = image(i, j);
			img(i, j, 0) = value.r;
			img(i, j, 1) = value.g;
			img(i, j, 2) = value.b;
		}
	}
	cimg_library::CImgDisplay disp;
	disp.display(img);
	getchar();
}
