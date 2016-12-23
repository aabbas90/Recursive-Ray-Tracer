#include <rt/textures/checkerboard.h>
#include <math.h>
#include <core/point.h>

namespace rt
{
    CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
    :white(white), black(black) {}

    RGBColor CheckerboardTexture::getColor(const Point& coord)
    {
        //lattice coordinates
        int lx = floor(coord.x);
        int ly = floor(coord.y);
        int lz = floor(coord.z);

        //compute parity
        int parity = (lx + ly + lz) % 2;
        if(parity == 1)
            return RGBColor::white();    
        else
            return RGBColor::black();    
    }
    RGBColor CheckerboardTexture::getColorDX(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    RGBColor CheckerboardTexture::getColorDY(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
}